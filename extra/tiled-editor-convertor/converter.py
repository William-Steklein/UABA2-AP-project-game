import os
import xml.etree.ElementTree as ET
from pathlib import Path


def get_filename_from_path(filepath: str):
    return os.path.basename(filepath)


def get_filename_from_path_without_extension(filepath: str):
    return get_filename_from_path(filepath).split('.')[0]


def convert_pixel_to_world_unit(number):
    return number * (0.25 / 16)


class Tileset:
    def __init__(self, tileset_filename: str):
        self.tiles = {}  # tile_id: TileSprite

        tree = ET.parse(tileset_filename)
        root = tree.getroot()

        for child in root:
            if child.tag == "tile":
                self.__add_child(child.attrib["id"], child[0])

    def __add_child(self, tile_id: str, tile_element):
        self.tiles[int(tile_id)] = WorldTileSrite(convert_pixel_to_world_unit(int(tile_element.attrib["width"])),
                                                  convert_pixel_to_world_unit(int(tile_element.attrib["height"])),
                                                  get_filename_from_path_without_extension(tile_element.attrib["source"]))

    def get_tile(self, tile_id: int):
        return self.tiles[tile_id]


class WorldWallEntity:
    def __init__(self, xpos: float, ypos: float, width: float, height: float, sliding: bool):
        self.xpos = xpos
        self.ypos = ypos

        self.width = width
        self.height = height

        self.sliding = sliding

    def get_position_string(self):
        return f"{self.xpos}, {self.ypos}"

    def get_size_string(self):
        if self.width != 0.25 or self.height != 0.25:
            return f"{self.width}, {self.height}"
        else:
            return ""

    def __str__(self):
        return f"2; {self.get_position_string()}; {self.get_size_string()}; {int(self.sliding)};"


class WorldTileSrite:
    def __init__(self, width: float, height: float, filename: str):
        self.width = width
        self.height = height
        self.filename = filename


class WorldTileEntity:
    def __init__(self, xpos, ypos, tile: WorldTileSrite, tile_type: int):
        self.xpos = xpos
        self.ypos = ypos

        self.tile = tile
        self.tile_type = tile_type

    def get_position_string(self):
        return f"{self.xpos}, {self.ypos}"

    def get_size_string(self):
        if self.tile.width != 0.25 or self.tile.height != 0.25:
            return f"{self.tile.width}, {self.tile.height}"
        else:
            return ""

    def __str__(self):
        return f"3; {self.get_position_string()}; {self.get_size_string()}; {self.tile_type}; {self.tile.filename};"


class WorldMap:
    def __init__(self, tile_map_filename, tilesets):
        self.tilesets = tilesets  # tileset_filename: TileSet
        self.tileset_id_offsets = {}  # tileset_filename: id_offset

        self.camera_move_time: float = 0

        self.walls = []
        self.slide_walls = []

        self.tiles_bg = []
        self.tiles_prop = []
        self.tiles_fg = []

        self.player_xpos = 0
        self.player_ypos = 0
        self.finish_xpos = 0
        self.finish_ypos = 0

        self.camera_start_xpos = 0
        self.camera_start_ypos = 0

        self.camera_end_xpos = 0
        self.camera_end_ypos = 0

        self.name = get_filename_from_path_without_extension(tile_map_filename)

        tree = ET.parse(tile_map_filename)
        root = tree.getroot()

        # tile size
        self.tile_width_pixel = int(root.attrib["tilewidth"])
        self.tile_height_pixel = int(root.attrib["tileheight"])

        # world map size
        self.width_tile = int(root.attrib["width"])
        self.height_tile = int(root.attrib["height"])

        self.width_pixel = self.width_tile * self.tile_width_pixel
        self.height_pixel = self.height_tile * self.tile_height_pixel

        # parse contents
        for child in root:
            if child.tag == "tileset":
                self.tileset_id_offsets[child.attrib["source"]] = int(child.attrib["firstgid"])

            if child.tag == "properties":
                # print(child[0].tag, child[0].attrib)
                self.__load_properties(child)

            elif child.tag == "objectgroup":
                if child.attrib["name"] == "wall":
                    self.__load_wall_layer(child, False)
                elif child.attrib["name"] == "slide_wall":
                    self.__load_wall_layer(child, True)
                elif child.attrib["name"] == "player":
                    self.__load_player_position(child)
                elif child.attrib["name"] == "finish":
                    self.__load_finish_position(child)
                elif child.attrib["name"] == "camera_start":
                    self.__load_camera_start(child)
                elif child.attrib["name"] == "camera_end":
                    self.__load_camera_end(child)
                elif child.attrib["name"] == "tile_bg":
                    self.__load_tile_object_layer(child, 0)
                elif child.attrib["name"] == "tile_prop":
                    self.__load_tile_object_layer(child, 1)
                elif child.attrib["name"] == "tile_fg":
                    self.__load_tile_object_layer(child, 2)

            elif child.tag == "layer":
                if child.attrib["name"] == "tile_bg":
                    self.__load_tile_layer(child, 0)
                elif child.attrib["name"] == "tile_prop":
                    self.__load_tile_layer(child, 1)
                elif child.attrib["name"] == "tile_fg":
                    self.__load_tile_layer(child, 2)

    def __str__(self):
        total = ""

        total += f"0; {self.player_xpos}, {self.player_ypos}; ;" + '\n'

        total += f"1; {self.finish_xpos}, {self.finish_ypos}; ;" + '\n'

        for wall in self.walls + self.slide_walls:
            total += wall.__str__() + '\n'

        for world_tile in self.tiles_bg + self.tiles_prop + self.tiles_fg:
            total += world_tile.__str__() + '\n'

        return total

    def __load_properties(self, properties_element):
        for property_element in properties_element:
            if property_element.attrib["name"] == "camera_move_time":
                self.camera_move_time = float(property_element.attrib["value"])

    def __get_tile(self, tile_id: int):
        current_tileset_id = next(iter(self.tileset_id_offsets))
        for tileset_id in self.tileset_id_offsets:
            if tile_id < self.tileset_id_offsets[tileset_id]:
                break
            current_tileset_id = tileset_id

        offset = self.tileset_id_offsets[current_tileset_id]

        return self.tilesets[current_tileset_id].get_tile(tile_id - offset)

    def __load_tile_layer(self, layer_element, tile_type: int = 0):
        layer_width_tile = int(layer_element.attrib["width"])
        layer_height_tile = int(layer_element.attrib["height"])

        x_tile_pos = 0
        y_tile_pos = layer_height_tile - 1

        # split tile_id csv into array and process
        for tile_id in layer_element[0].text[1:-1].replace('\n', '').split(','):
            if tile_id != '0':
                tile_list = []

                if tile_type == 0:
                    tile_list = self.tiles_bg
                elif tile_type == 1:
                    tile_list = self.tiles_prop
                elif tile_type == 2:
                    tile_list = self.tiles_fg

                tile_sprite = self.__get_tile(int(tile_id))

                tile_list.append(
                    WorldTileEntity(convert_pixel_to_world_unit(x_tile_pos * self.tile_width_pixel) + tile_sprite.width / 2,
                                    convert_pixel_to_world_unit(
                                        y_tile_pos * self.tile_height_pixel) + tile_sprite.height / 2,
                                    tile_sprite, tile_type))

            x_tile_pos += 1
            if x_tile_pos == layer_width_tile:
                x_tile_pos = 0
                y_tile_pos -= 1

    def __load_wall_layer(self, layer_element, sliding: bool):
        for child in layer_element:
            wall_list = []

            if sliding:
                wall_list = self.slide_walls
            else:
                wall_list = self.walls

            wall_width = convert_pixel_to_world_unit(int(child.attrib["width"]))
            wall_height = convert_pixel_to_world_unit(int(child.attrib["height"]))

            wall_xpos = convert_pixel_to_world_unit(int(child.attrib["x"]) + (int(child.attrib["width"]) / 2))
            wall_ypos = convert_pixel_to_world_unit(
                -(int(child.attrib["y"]) + (int(child.attrib["height"]) / 2) - self.height_pixel))

            wall_list.append(WorldWallEntity(wall_xpos,
                                             wall_ypos,
                                             wall_width,
                                             wall_height,
                                             sliding))

    def __convert_position(self, xpos_pixel, ypos_pixel, width_world=0.25, height_world=0.25):
        return [convert_pixel_to_world_unit(xpos_pixel) + (width_world / 2),
                convert_pixel_to_world_unit(-(ypos_pixel - self.height_pixel)) + (height_world / 2)]

    def __load_player_position(self, layer_element):
        position = self.__convert_position(int(layer_element[0].attrib["x"]), int(layer_element[0].attrib["y"]))

        self.player_xpos = position[0]
        self.player_ypos = position[1]

    def __load_finish_position(self, layer_element):
        position = self.__convert_position(int(layer_element[0].attrib["x"]), int(layer_element[0].attrib["y"]))

        self.finish_xpos = position[0]
        self.finish_ypos = position[1]

    def __load_camera_start(self, layer_element):
        if not layer_element:
            return

        position = self.__convert_position(int(layer_element[0].attrib["x"]), int(layer_element[0].attrib["y"]))

        self.camera_start_xpos = position[0]
        self.camera_start_ypos = position[1]

    def __load_camera_end(self, layer_element):
        if not layer_element:
            return

        position = self.__convert_position(int(layer_element[0].attrib["x"]), int(layer_element[0].attrib["y"]))

        self.camera_end_xpos = position[0]
        self.camera_end_ypos = position[1]

    def __load_tile_object_layer(self, layer_element, tile_type: int):
        for tile_object in layer_element:
            tile_sprite = self.__get_tile(int(tile_object.attrib["gid"]))

            position = self.__convert_position(int(tile_object.attrib["x"]), int(tile_object.attrib["y"]),
                                               tile_sprite.width, tile_sprite.height)

            tile_list = []

            if tile_type == 0:
                tile_list = self.tiles_bg
            elif tile_type == 1:
                tile_list = self.tiles_prop
            elif tile_type == 2:
                tile_list = self.tiles_fg

            tile_list.append(
                WorldTileEntity(position[0], position[1], tile_sprite, tile_type))

    def get_center_world(self):
        return f"{convert_pixel_to_world_unit(self.width_pixel / 2)}, {convert_pixel_to_world_unit(self.height_pixel / 2)}"

    def get_limit_world(self):
        return f"{convert_pixel_to_world_unit(self.width_pixel)}, {convert_pixel_to_world_unit(self.height_pixel)}"


class Converter:
    def __init__(self, tileset_directory: str, map_directory: str):
        self.tilesets = {}  # tileset_filename: TileSet
        self.world_maps = []

        self.__load_tilesets(tileset_directory)
        self.__load_maps(map_directory)

    def __load_tilesets(self, directory: str):
        for filepath in Path(directory).glob("*.tsx"):
            self.tilesets[get_filename_from_path(str(filepath))] = Tileset(str(filepath))

    def __load_maps(self, directory: str):
        for filepath in Path(directory).glob("*.tmx"):
            self.world_maps.append(WorldMap(str(filepath), self.tilesets))

    def create_world_files(self):
        for world_map in self.world_maps:
            Path("./output").mkdir(parents=True, exist_ok=True)
            f = open(f"./output/{world_map.name}.world", "w")

            f.write("-meta\n")
            f.write(f"origin= {world_map.get_center_world()}\n")
            f.write(f"limit= {world_map.get_limit_world()}\n")

            f.write("\n")

            f.write(f"camera_move_time= {world_map.camera_move_time}\n")
            f.write(f"camera_start= {world_map.camera_start_xpos}, {world_map.camera_start_ypos}\n")
            f.write(f"camera_end= {world_map.camera_end_xpos}, {world_map.camera_end_ypos}\n")

            f.write("\n")

            f.write("-entities\n")
            f.write(world_map.__str__())
            pass

        return ""

    def create_resource_file(self, tile_set_filename: str, new_path: str):
        return ""


if __name__ == "__main__":
    convertor = Converter("./input/tileset/", "./input/map/")

    convertor.create_world_files()
