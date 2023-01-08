import os
import xml.etree.ElementTree as ET
from pathlib import Path


class Vector2:
    def __init__(self, x: float, y: float):
        self.x: float = x
        self.y: float = y

    def __str__(self):
        return f"{self.x}, {self.y}"

    def __add__(self, other):
        return Vector2(self.x + other.x, self.y + other.y)

    def __truediv__(self, other):
        return Vector2(self.x / other, self.y / other)


def parse_Vector2_from_string(string: str):
    string_list = string.split(',')
    return Vector2(int(string_list[0]), int(string_list[1]))


def get_filename_from_path(filepath: str):
    return os.path.basename(filepath)


def get_filename_from_path_without_extension(filepath: str):
    return get_filename_from_path(filepath).split('.')[0]


def convert_pixel_to_world_unit(number):
    return number * (0.25 / 16)


def convert_world_unit_to_pixel(number):
    return number * (16 / 0.25)


def convert_vector2_pixel_to_world_unit(x, y):
    return Vector2(convert_pixel_to_world_unit(x), convert_pixel_to_world_unit(y))


class TileSprite:
    def __init__(self, size: Vector2, filename: str):
        self.size: Vector2 = size
        self.filename = filename


class Tileset:
    def __init__(self, tileset_filename: str):
        self.tiles = {}  # tile_id: TileSprite

        tree = ET.parse(tileset_filename)
        root = tree.getroot()

        for child in root:
            if child.tag == "tile":
                tile_id = int(child.attrib["id"])
                tile_element = child[0]

                self.tiles[tile_id] = TileSprite(
                    convert_vector2_pixel_to_world_unit(int(tile_element.attrib["width"]),
                                                        int(tile_element.attrib["height"])),
                    get_filename_from_path_without_extension(tile_element.attrib["source"]))


class WorldTileEntity:
    def __init__(self, position: Vector2, tile: TileSprite, tile_type: int):
        self.position: Vector2 = position

        self.tile = tile
        self.tile_type = tile_type

    def __str__(self):
        return f"3; {self.position}; {self.tile.size}; {self.tile_type}; {self.tile.filename};"


class WorldWallEntity:
    def __init__(self, position: Vector2, size: Vector2, sliding: bool):
        self.position: Vector2 = position
        self.size: Vector2 = size

        self.sliding = sliding

    def __str__(self):
        return f"2; {self.position}; {self.size}; {int(self.sliding)};"


class WorldMap:
    def __init__(self, tile_map_filename, tilesets):
        self.tilesets = tilesets  # tileset_filename: TileSet
        self.tileset_id_offsets = {}  # tileset_filename: id_offset

        self.walls = []
        self.slide_walls = []

        self.tiles_bg = []
        self.tiles_prop = []
        self.tiles_fg = []

        self.player_position: Vector2 = Vector2(0, 0)
        self.finish_position: Vector2 = Vector2(0, 0)

        self.camera_start_position: Vector2 = Vector2(0, 0)
        self.camera_end_position: Vector2 = Vector2(0, 0)
        self.camera_move_time: float = 0
        self.camera_pos_y_lock: bool = False

        self.name = get_filename_from_path_without_extension(tile_map_filename)

        tree = ET.parse(tile_map_filename)
        root = tree.getroot()

        # tile size
        self.tile_width_pixel = int(root.attrib["tilewidth"])
        self.tile_height_pixel = int(root.attrib["tileheight"])

        # world map size
        self.width_pixel = int(root.attrib["width"]) * self.tile_width_pixel
        self.height_pixel = int(root.attrib["height"]) * self.tile_height_pixel

        self.size = convert_vector2_pixel_to_world_unit(self.width_pixel, self.height_pixel)
        self.center = self.size / 2

        # parse contents
        for child in root:
            if child.tag == "tileset":
                self.tileset_id_offsets[get_filename_from_path(child.attrib["source"])] = int(child.attrib["firstgid"])

            if child.tag == "properties":
                self.__load_properties(child)

            elif child.tag == "objectgroup":
                if child.attrib["name"] == "wall":
                    self.__load_wall_object_layer(child, False)
                elif child.attrib["name"] == "slide_wall":
                    self.__load_wall_object_layer(child, True)

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

        total += f"0; {self.player_position}; ;" + '\n'

        total += f"1; {self.finish_position}; ;" + '\n'

        for wall in self.walls + self.slide_walls:
            total += wall.__str__() + '\n'

        for world_tile in self.tiles_bg + self.tiles_prop + self.tiles_fg:
            total += world_tile.__str__() + '\n'

        return total

    def __load_properties(self, properties_element):
        for property_element in properties_element:
            property_name = property_element.attrib["name"]
            property_value = property_element.attrib["value"]

            if property_name == "camera_move_time":
                self.camera_move_time = float(property_value)
            elif property_name == "player_pos":
                self.player_position = self.__convert_vector2_position_pixel_to_world_unit(
                    parse_Vector2_from_string(property_value), Vector2(0.25, 0.25), True)
            elif property_name == "finish_pos":
                self.finish_position = self.__convert_vector2_position_pixel_to_world_unit(
                    parse_Vector2_from_string(property_value), Vector2(0.25, 0.25), True)
            elif property_name == "camera_start":
                self.camera_start_position = self.__convert_vector2_position_pixel_to_world_unit(
                    parse_Vector2_from_string(property_value), Vector2(0.25, 0.25), True)
            elif property_name == "camera_end":
                self.camera_end_position = self.__convert_vector2_position_pixel_to_world_unit(
                    parse_Vector2_from_string(property_value), Vector2(0.25, 0.25), True)
            elif property_name == "camera_pos_y_lock":
                self.camera_pos_y_lock = property_value == "true"

    def __convert_vector2_position_pixel_to_world_unit(self, position_pixel: Vector2,
                                                       entity_world_size: Vector2 = Vector2(0.25, 0.25),
                                                       is_object: bool = False):
        offset = entity_world_size / 2
        if is_object:
            offset.y *= -1
        return convert_vector2_pixel_to_world_unit(position_pixel.x,
                                                   -(position_pixel.y - self.height_pixel)) + offset

    def __get_tile(self, tile_id: int):
        current_tileset_id = next(iter(self.tileset_id_offsets))
        for tileset_id in self.tileset_id_offsets:
            if tile_id < self.tileset_id_offsets[tileset_id]:
                break
            current_tileset_id = tileset_id

        offset = self.tileset_id_offsets[current_tileset_id]

        return self.tilesets[current_tileset_id].tiles[tile_id - offset]

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

                position = convert_vector2_pixel_to_world_unit(
                    x_tile_pos * self.tile_width_pixel,
                    y_tile_pos * self.tile_height_pixel
                ) + (tile_sprite.size / 2)

                tile_list.append(WorldTileEntity(
                    position,
                    tile_sprite,
                    tile_type
                ))

            x_tile_pos += 1
            if x_tile_pos == layer_width_tile:
                x_tile_pos = 0
                y_tile_pos -= 1

    def __load_wall_object_layer(self, layer_element, sliding: bool):
        for child in layer_element:
            wall_list = []

            if sliding:
                wall_list = self.slide_walls
            else:
                wall_list = self.walls

            wall_size = convert_vector2_pixel_to_world_unit(int(child.attrib["width"]), int(child.attrib["height"]))
            wall_position = self.__convert_vector2_position_pixel_to_world_unit(
                Vector2(int(child.attrib["x"]), int(child.attrib["y"])),
                wall_size,
                True
            )

            wall_list.append(WorldWallEntity(wall_position, wall_size, sliding))

    def __load_tile_object_layer(self, layer_element, tile_type: int):
        for tile_object in layer_element:
            tile_sprite = self.__get_tile(int(tile_object.attrib["gid"]))

            position = self.__convert_vector2_position_pixel_to_world_unit(
                Vector2(int(tile_object.attrib["x"]),
                        int(tile_object.attrib["y"])),
                tile_sprite.size
            )

            tile_list = []

            if tile_type == 0:
                tile_list = self.tiles_bg
            elif tile_type == 1:
                tile_list = self.tiles_prop
            elif tile_type == 2:
                tile_list = self.tiles_fg

            tile_list.append(
                WorldTileEntity(position, tile_sprite, tile_type)
            )


class Converter:
    def __init__(self, tileset_directory: str, map_directory: str, output_directory: str = "./output"):
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
            f = open((Path("./output", world_map.name).with_suffix(".world")), "w")

            f.write("-meta\n")
            f.write(f"origin= {world_map.center}\n")
            f.write(f"limit= {world_map.size}\n")

            f.write("\n")

            f.write(f"camera_move_time= {world_map.camera_move_time}\n")
            f.write(f"camera_start= {world_map.camera_start_position}\n")
            f.write(f"camera_end= {world_map.camera_end_position}\n")
            f.write(f"camera_pos_y_lock= {int(world_map.camera_pos_y_lock)}\n")

            f.write("\n")

            f.write("-entities\n")
            f.write(world_map.__str__())

            f.close()

    def create_resource_file(self, tileset_name: str, resource_path: str, new_filepath: str):
        os.makedirs(os.path.dirname(new_filepath), exist_ok=True)
        f = open(Path(new_filepath), "w")

        first = True

        f.write("{\n")

        # for tileset in self.tilesets.values():
        for tile in self.tilesets[tileset_name].tiles.values():
            if not first:
                f.write(",\n")
            else:
                first = False

            f.write(
                f"\t\"{tile.filename}\": \"{Path(resource_path, tile.filename).with_suffix('.png').as_posix()}\"")

        f.write("\n}")

        f.close()


if __name__ == "__main__":
    convertor = Converter("./game-engine-tiled-editor-project/", "./game-engine-tiled-editor-project/levels/")

    convertor.create_resource_file("terrain.tsx", "data/textures/tiles/terrain/",
                                   "./output/resource-info/tile_terrain_textures.json")
    convertor.create_resource_file("props.tsx", "data/textures/tiles/props/",
                                   "./output/resource-info/tile_prop_textures.json")

    convertor.create_world_files()
