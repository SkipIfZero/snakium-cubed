#pragma once
#ifndef S3_ASSETS_HPP
#define S3_ASSETS_HPP

#include "sfz/SDL.hpp"
#include "sfz/GL.hpp"
#include <string>

namespace s3 {

struct Assets final {
	gl::Texture HEAD_D2U_F1,
	            HEAD_D2U_F2,

				PRE_HEAD_D2U_F1,
				PRE_HEAD_D2U_DIG_F1,
				PRE_HEAD_D2R_F1,
				PRE_HEAD_D2R_DIG_F1,

				DEADHEAD_D2U_F3,
				DEADHEAD_D2U_DIG_F3,
				DEADHEAD_D2R_F3,
				DEADHEAD_D2R_DIG_F3,

				BODY_D2U,
				BODY_D2U_DIG,
				BODY_D2R,
				BODY_D2R_DIG,

				TAIL_D2U_F1,
				TAIL_D2U_F2,
				TAIL_D2U_DIG_F1,
				TAIL_D2U_DIG_F2,
				TAIL_D2R_F1,
				TAIL_D2R_F2,
				TAIL_D2R_DIG_F1,
				TAIL_D2R_DIG_F2,

				BUTTON_LEFT,
				BUTTON_LEFT_TOUCHED,
				BUTTON_LEFT_DISABLED,
				BUTTON_MIDDLE_TOUCHED,
				BUTTON_RIGHT,
				BUTTON_RIGHT_TOUCHED,
				BUTTON_RIGHT_DISABLED,

				OBJECT,
				BONUS_OBJECT,
				FILLED,
				TILE_BORDER;

	Assets() noexcept;
	~Assets() noexcept = default;
	Assets(const Assets&) = delete;
	Assets& operator= (const Assets&) = delete;
};

} // namespace s3

#endif