#pragma once
#ifndef S3_ASSETS_HPP
#define S3_ASSETS_HPP

#include <sfz/SDL.hpp>
#include <sfz/GL.hpp>
#include <string>
#include "GameLogic.hpp"

namespace s3 {

struct Assets final {

	gl::SpriteBatch mSpriteBatch;
	gl::FontRenderer mFontRenderer;

	gl::Texture HEAD_D2U_F1,
	            HEAD_D2U_F2,

				PRE_HEAD_D2U_F1,
				PRE_HEAD_D2U_DIG_F1,
				PRE_HEAD_D2R_F1,
				PRE_HEAD_D2R_DIG_F1,

				DEAD_PRE_HEAD_D2U_F1,
				DEAD_PRE_HEAD_D2U_DIG_F1,
				DEAD_PRE_HEAD_D2R_F1,
				DEAD_PRE_HEAD_D2R_DIG_F1,

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
				TILE_FACE;

	Assets() noexcept;
	~Assets() noexcept = default;
	Assets(const Assets&) = delete;
	Assets& operator= (const Assets&) = delete;

	const gl::Texture& getTileTexture(SnakeTile* tilePtr, float progress, bool gameOver) const noexcept;
};

} // namespace s3

#endif