#ifndef GAME_ENGINE_CONSTANTS_H
#define GAME_ENGINE_CONSTANTS_H


#include <engine/math/Vector2f.h>

namespace game {

    namespace constants {

        namespace layer {

            extern const unsigned int bg_1;
            extern const unsigned int bg_2;
            extern const unsigned int bg_3;
            extern const unsigned int bg_4;
            extern const unsigned int bg_5;

            extern const unsigned int tile_bg;
            extern const unsigned int tile_prop;
            extern const unsigned int player;
            extern const unsigned int finish;
            extern const unsigned int tile_fg;
            extern const unsigned int vfx;

            extern const unsigned int debug_wall_hit_box;
            extern const unsigned int debug_finish_hit_box;

            extern const unsigned int debug_player_hit_box;
            extern const unsigned int debug_player_wall_slide_ray;
            extern const unsigned int debug_player_standing_ray;

            extern const unsigned int ui_bg;
            extern const unsigned int ui_menu;
            extern const unsigned int ui_button;
            extern const unsigned int ui_text;

            extern const unsigned int side_bar;

        }

        namespace size {

            extern const engine::Vector2f player;
            extern const engine::Vector2f finish;
            extern const engine::Vector2f wall;
            extern const engine::Vector2f tile;

        }

        namespace player {

            extern const float jump_dt;
            extern const float jump_height;

            extern const float mass;
            extern const float horizontal_movement_force;

        } // player

        namespace ui {

            extern const float scale_factor;

            namespace menu {

                extern const engine::Vector2f position;
                extern const engine::Vector2f size;

                extern const engine::Vector2f button_position_1;
                extern const engine::Vector2f button_position_2;
                extern const engine::Vector2f button_position_3;
                extern const engine::Vector2f button_position_4;

                extern const engine::Vector2f button_size;
                extern const float font_size;

            }

            namespace level_menu {

                extern const engine::Vector2f level_select_button_size;
                extern const engine::Vector2f arrow_button_size;
                extern const engine::Vector2f return_button_position;

            }

        }

    } // constants

} // game

#endif //GAME_ENGINE_CONSTANTS_H
