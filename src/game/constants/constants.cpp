#include "constants.h"

namespace game {
    namespace constants {

        namespace layer {

            const unsigned int bg_1 = 0;
            const unsigned int bg_2 = 1;
            const unsigned int bg_3 = 2;
            const unsigned int bg_4 = 3;
            const unsigned int bg_5 = 4;

            const unsigned int tile_bg = 5;
            const unsigned int player = 6;
            const unsigned int finish = 7;
            const unsigned int tile_prop = 8;
            const unsigned int tile_fg = 9;
            const unsigned int vfx = 10;

            const unsigned int debug_wall_hit_box = 20;
            const unsigned int debug_finish_hit_box = 21;

            const unsigned int debug_player_hit_box = 22;
            const unsigned int debug_player_wall_slide_ray = 23;
            const unsigned int debug_player_standing_ray = 24;

            const unsigned int ui_bg = 31;
            const unsigned int ui_menu = 32;
            const unsigned int ui_button = 33;
            const unsigned int ui_text = 34;

            const unsigned int side_bar = 40;

        }

        namespace size {

            const engine::Vector2f player = {0.60f, 0.444f};
            const engine::Vector2f finish = {0.25, 0.25};
            const engine::Vector2f wall = {0.25, 0.25};
            const engine::Vector2f tile = {0.25, 0.25};

        }

        namespace player {


            const float mass = 20;

            const float jump_dt = 0.5;
            const float jump_height = 1;

            const float horizontal_movement_force = 200;
            const float initial_jump_velocity = 2 * jump_height / jump_dt;

            const float wall_horizontal_jump_velocity = initial_jump_velocity * 0.75f;
            const engine::Vector2f gravitational_acceleration = {0, -2 * jump_height / (jump_dt * jump_dt)};;

            const engine::Vector2f horizontal_velocity_cap = {-3.5f, 3.5f};
            const engine::Vector2f vertical_velocity_cap = {-initial_jump_velocity * 1.25f,
                                                            initial_jump_velocity * 1.25f};

            const engine::Vector2f wall_vertical_velocity_cap = {-initial_jump_velocity * 0.5f,
                                                                 initial_jump_velocity * 0.5f};

            extern const float stopping_friction = 250.f;
            extern const float sliding_friction = 50.f;

        } // player

        namespace ui {

            const float scale_factor = 1.55f;

            namespace menu {

                const engine::Vector2f position = {0, 0};
                const engine::Vector2f size = engine::Vector2f(1, 1.5) * scale_factor;

                const engine::Vector2f button_position_1 = engine::Vector2f(0, 0.51) * scale_factor;
                const engine::Vector2f button_position_2 = engine::Vector2f(0, 0.175) * scale_factor;
                const engine::Vector2f button_position_3 = engine::Vector2f(0, -0.175) * scale_factor;
                const engine::Vector2f button_position_4 = engine::Vector2f(0, -0.51) * scale_factor;

                const engine::Vector2f button_size = engine::Vector2f(0.5, 0.25) * scale_factor;
                extern const float font_size = 0.085f * scale_factor;
            }

            namespace level_menu {

                const engine::Vector2f level_select_button_size = engine::Vector2f(0.3, 0.3) * scale_factor;
                const engine::Vector2f arrow_button_size = engine::Vector2f(0.3, 0.3) * scale_factor;

                const engine::Vector2f return_button_position = engine::Vector2f(0, -0.75) * scale_factor;

            }

        }
    } // constants
} // game