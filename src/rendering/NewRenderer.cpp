#include "rendering/NewRenderer.hpp"

#include <sfz/gl/OpenGL.hpp>
#include <sfz/math/Vector.hpp>
#include <sfz/util/IO.hpp>

#include "rendering/Assets.hpp"

namespace s3 {

using sfz::vec2;
using sfz::vec3;
using sfz::vec4;

// Static functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

static gl::Program compileStandardShaderProgram() noexcept
{
	return gl::Program::fromFile((sfz::basePath() + "assets/shaders/shader.vert").c_str(),
	                             (sfz::basePath() + "assets/shaders/shader.frag").c_str(),
	                             [](uint32_t shaderProgram) {
		glBindAttribLocation(shaderProgram, 0, "inPosition");
		glBindAttribLocation(shaderProgram, 1, "inNormal");
		//glBindAttribLocation(shaderProgram, 2, "inUV"); // Not available for snakium models
		glBindAttribLocation(shaderProgram, 3, "inMaterialID");
		glBindFragDataLocation(shaderProgram, 0, "outFragColor");
	});
}

static gl::Model& getTileModel(SnakeTile* tilePtr, float progress, bool gameOver) noexcept
{
	Assets& a = Assets::INSTANCE();
	const bool rightTurn = isRightTurn(tilePtr->from(), tilePtr->to());
	const bool leftTurn = isLeftTurn(tilePtr->from(), tilePtr->to());
	const bool frame1 = progress <= 0.5f;

	switch (tilePtr->type()) {
	//case s3::TileType::EMPTY: return assets.TILE_FACE;
	//case s3::TileType::OBJECT: return assets.OBJECT;
	//case s3::TileType::BONUS_OBJECT: return assets.BONUS_OBJECT;

	case TileType::HEAD:
		if (frame1) return a.HEAD_D2U_F1_MODEL;
		else return a.HEAD_D2U_F2_MODEL;
		
	case TileType::PRE_HEAD:
		if (frame1) {
			if (rightTurn) return (!gameOver) ? a.PRE_HEAD_D2R_F1_MODEL : a.DEAD_PRE_HEAD_D2R_F1_MODEL;
			else if (leftTurn) return (!gameOver) ? a.PRE_HEAD_D2L_F1_MODEL : a.DEAD_PRE_HEAD_D2L_F1_MODEL;
			else return (!gameOver) ? a.PRE_HEAD_D2U_F1_MODEL : a.DEAD_PRE_HEAD_D2U_F1_MODEL;
		} else {
			if (rightTurn) return a.BODY_D2R_MODEL;
			else if (leftTurn) return a.BODY_D2L_MODEL;
			else return a.BODY_D2U_MODEL;
		}

	case TileType::BODY:
		if (rightTurn) return a.BODY_D2R_MODEL;
		else if (leftTurn) return a.BODY_D2L_MODEL;
		else return a.BODY_D2U_MODEL;

	case TileType::TAIL:
		if (frame1) {
			if (rightTurn) return a.TAIL_D2R_F1_MODEL;
			else if (leftTurn) return a.TAIL_D2L_F1_MODEL;
			else return a.TAIL_D2U_F1_MODEL;
		} else {
			if (rightTurn) return a.TAIL_D2R_F2_MODEL;
			else if (leftTurn) return a.TAIL_D2L_F2_MODEL;
			else return a.TAIL_D2U_F2_MODEL;
		}

	case TileType::HEAD_DIGESTING:
		if (frame1) return a.HEAD_D2U_F1_MODEL;
		else return a.HEAD_D2U_F2_MODEL;

	case TileType::PRE_HEAD_DIGESTING:
		if (frame1) {
			if (rightTurn) return (!gameOver) ? a.PRE_HEAD_D2R_DIG_F1_MODEL : a.DEAD_PRE_HEAD_D2R_DIG_F1_MODEL;
			else if (leftTurn) return (!gameOver) ? a.PRE_HEAD_D2L_DIG_F1_MODEL : a.DEAD_PRE_HEAD_D2L_DIG_F1_MODEL;
			else return (!gameOver) ? a.PRE_HEAD_D2U_DIG_F1_MODEL : a.DEAD_PRE_HEAD_D2U_DIG_F1_MODEL;
		} else {
			if (rightTurn) return a.BODY_D2R_DIG_MODEL;
			else if (leftTurn) return a.BODY_D2L_DIG_MODEL;
			else return a.BODY_D2U_DIG_MODEL;
		}

	case TileType::BODY_DIGESTING:
		if (rightTurn) return a.BODY_D2R_DIG_MODEL;
		else if (leftTurn) return a.BODY_D2L_DIG_MODEL;
		else return a.BODY_D2U_DIG_MODEL;

	case TileType::TAIL_DIGESTING:
		if (frame1) {
			if (rightTurn) return a.TAIL_D2R_DIG_F1_MODEL;
			else if (leftTurn) return a.TAIL_D2L_DIG_F1_MODEL;
			else return a.TAIL_D2U_DIG_F1_MODEL;
		} else {
			if (rightTurn) return a.TAIL_D2R_DIG_F2_MODEL;
			if (leftTurn) return a.TAIL_D2L_DIG_F2_MODEL;
			else return a.TAIL_D2U_DIG_F2_MODEL;
		}
	}

	return a.NOT_FOUND_MODEL;
}

static float getTileAngleRad(Direction3D side, Direction2D from) noexcept
{
	float angle;

	switch (from) {
	case Direction2D::UP:
		angle = 180.0f;
		break;
	case Direction2D::DOWN:
		angle = 0.0f;
		break;
	case Direction2D::LEFT:
		angle = -90.0f;
		break;
	case Direction2D::RIGHT:
		angle = 90.0f;
		break;
	}

	// Yeah, I dunno. There probably is a pattern here to make it general, but I don't see it.
	switch (side) {
	case Direction3D::NORTH:
		angle += 180.0f;
		break;
	case Direction3D::SOUTH:
		// Do nothing.
		break;
	case Direction3D::WEST:
		angle -= 90.0f;
		break;
	case Direction3D::EAST:
		angle += 90.0f;
		break;
	case Direction3D::UP:
		angle += 180.0f;
		break;
	case Direction3D::DOWN:
		// Do nothing.
		break;
	}

	return angle * sfz::DEG_TO_RAD();
}

static vec3 tilePosToVector(const Model& model, const Position& tilePos) noexcept
{
	// +0.5f to get the midpoint of the tile
	const float e1f = static_cast<float>(tilePos.e1) + 0.5f;
	const float e2f = static_cast<float>(tilePos.e2) + 0.5f;
	const float tileWidth = 1.0f / static_cast<float>(model.mCfg.gridWidth);

	return (e1f * tileWidth - 0.5f) * directionVector(tilePos.side, Coordinate::e1) +
		(e2f * tileWidth - 0.5f) * directionVector(tilePos.side, Coordinate::e2) +
		toVector(tilePos.side) * 0.5f;
}

static mat4 tileSpaceRotation(Direction3D side) noexcept
{
	switch (side) {
	case Direction3D::UP: return sfz::identityMatrix4<float>();
	case Direction3D::DOWN: return sfz::xRotationMatrix4(sfz::PI());
	case Direction3D::SOUTH: return sfz::xRotationMatrix4(sfz::PI()/2.0f);
	case Direction3D::NORTH: return sfz::xRotationMatrix4(-sfz::PI()/2.0f);
	case Direction3D::WEST: return sfz::zRotationMatrix4(sfz::PI()/2.0f);
	case Direction3D::EAST: return sfz::zRotationMatrix4(-sfz::PI()/2.0f);
	}
}

static vec3 tileColor(const SnakeTile* tilePtr) noexcept
{
	switch (tilePtr->type()) {

	case s3::TileType::OBJECT:
		return vec3(0.0f, 1.0f, 1.0f);

	case s3::TileType::BONUS_OBJECT:
		return vec3{1.0f, 0.0f, 0.0f};

	case s3::TileType::HEAD:
	case s3::TileType::PRE_HEAD:
	case s3::TileType::BODY:
	case s3::TileType::TAIL:
		return vec3{0.0f, 1.0f, 0.25f};

	case s3::TileType::HEAD_DIGESTING:
	case s3::TileType::PRE_HEAD_DIGESTING:
	case s3::TileType::BODY_DIGESTING:
	case s3::TileType::TAIL_DIGESTING:
		return vec3{0.0f, 1.0f, 0.5f};

	case s3::TileType::EMPTY:
	default:
		return vec3{1.0f, 1.0f, 1.0f};
	}
}

// NewRenderer: Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

NewRenderer::NewRenderer() noexcept
:
	mProgram{s3::compileStandardShaderProgram()}
{ }

// NewRenderer: Public methods
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void NewRenderer::render(const Model& model, const Camera& cam, const AABB2D& viewport) noexcept
{
	Assets& assets = Assets::INSTANCE();

	mProgram.reload();

	float aspect = viewport.width() / viewport.height();
	mProjMatrix = sfz::glPerspectiveProjectionMatrix(cam.mFov, aspect, 0.1f, 50.0f);

	//glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	// Clearing screen
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable culling
	glEnable(GL_CULL_FACE);

	glViewport(viewport.min.x, viewport.min.y, viewport.width(), viewport.height());

	glUseProgram(mProgram.handle());

	const mat4 viewMatrix = cam.mViewMatrix;
	gl::setUniform(mProgram, "uProjMatrix", mProjMatrix);
	
	// Render all SnakeTiles
	const size_t tilesPerSide = model.mCfg.gridWidth*model.mCfg.gridWidth;
	const mat4 tileScaling = sfz::scalingMatrix4(1.0f / (16.0f * (float)model.mCfg.gridWidth));
	//vec3 snakeFloatVec;

	for (size_t side = 0; side < 6; side++) {
		Direction3D currentSide = cam.mSideRenderOrder[side];
		SnakeTile* sidePtr = model.getTilePtr(Position{currentSide, 0, 0});

		mat4 tileSpaceRot = tileSpaceRotation(currentSide);
		mat4 tileSpaceRotScaling = tileSpaceRot * tileScaling;
		//snakeFloatVec = toVector(currentSide) * 0.001f;

		if (cam.mRenderTileFaceFirst[side]) {
			for (size_t i = 0; i < tilesPerSide; i++) {
				SnakeTile* tilePtr = sidePtr + i;
				Position tilePos = model.getTilePosition(tilePtr);

				// Skip empty tiles
				if (tilePtr->type() == s3::TileType::EMPTY) continue;

				// Calculate base transform
				mat4 transform = tileSpaceRotScaling;
				transform *= sfz::yRotationMatrix4(getTileAngleRad(tilePos.side, tilePtr->from()));
				sfz::translation(transform, tilePosToVector(model, tilePos));

				// Set uniforms
				const mat4 modelViewMatrix = viewMatrix * transform;
				const mat4 normalMatrix = sfz::inverse(sfz::transpose(modelViewMatrix));
				gl::setUniform(mProgram, "uModelViewMatrix", modelViewMatrix);
				gl::setUniform(mProgram, "uNormalMatrix", normalMatrix);
				gl::setUniform(mProgram, "uColor", tileColor(tilePtr));

				// Render tile model
				getTileModel(tilePtr, model.mProgress, model.mGameOver).render();
			}
		} else {
			for (size_t i = 0; i < tilesPerSide; i++) {
				SnakeTile* tilePtr = sidePtr + i;
				Position tilePos = model.getTilePosition(tilePtr);

				// Skip empty tiles
				if (tilePtr->type() == s3::TileType::EMPTY) continue;

				// Calculate base transform
				mat4 transform = tileSpaceRotScaling;
				transform *= sfz::yRotationMatrix4(getTileAngleRad(tilePos.side, tilePtr->from()));
				sfz::translation(transform, tilePosToVector(model, tilePos));

				// Set uniforms
				const mat4 modelViewMatrix = viewMatrix * transform;
				const mat4 normalMatrix = sfz::inverse(sfz::transpose(modelViewMatrix));
				gl::setUniform(mProgram, "uModelViewMatrix", modelViewMatrix);
				gl::setUniform(mProgram, "uNormalMatrix", normalMatrix);
				gl::setUniform(mProgram, "uColor", tileColor(tilePtr));

				// Render tile model
				getTileModel(tilePtr, model.mProgress, model.mGameOver).render();
			}
		}
	}

	// Render dead snake head if game over
	if (model.mGameOver) {
		SnakeTile* tilePtr = model.mDeadHeadPtr;
		Position tilePos = model.mDeadHeadPos;

		mat4 tileSpaceRot = tileSpaceRotation(tilePos.side);
		mat4 tileSpaceRotScaling = tileSpaceRot * tileScaling;

		// Calculate base transform
		mat4 transform = tileSpaceRotScaling;
		transform *= sfz::yRotationMatrix4(getTileAngleRad(tilePos.side, tilePtr->from()));
		sfz::translation(transform, tilePosToVector(model, tilePos));

		// Set uniforms
		const mat4 modelViewMatrix = viewMatrix * transform;
		const mat4 normalMatrix = sfz::inverse(sfz::transpose(modelViewMatrix));
		gl::setUniform(mProgram, "uModelViewMatrix", modelViewMatrix);
		gl::setUniform(mProgram, "uNormalMatrix", normalMatrix);
		gl::setUniform(mProgram, "uColor", tileColor(tilePtr));

		// Render tile model
		getTileModel(tilePtr, model.mProgress, model.mGameOver).render();
	}

	gl::FontRenderer& font = assets.fontRenderer;

	font.verticalAlign(gl::VerticalAlign::TOP);
	font.horizontalAlign(gl::HorizontalAlign::LEFT);

	font.begin(viewport); // TODO: Should not use viewport

	font.write(vec2{0.0f, (float)viewport.height()}, 64.0f, "Score: " + std::to_string(model.mScore));

	font.end(0, viewport.dimensions(), vec4{1.0f, 1.0f, 1.0f, 1.0f});

	if (model.mGameOver) {
		font.verticalAlign(gl::VerticalAlign::MIDDLE);
		font.horizontalAlign(gl::HorizontalAlign::CENTER);

		font.begin(viewport);

		font.write(viewport.position(), 160.0f, "Game Over");

		font.end(0, viewport.dimensions(), sfz::vec4{1.0f, 1.0f, 1.0f, 1.0f});
	}

	// Clean up
	glUseProgram(0);
}

} // namespace s3