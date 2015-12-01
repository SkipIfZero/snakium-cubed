#pragma once
#ifndef SFZ_GL_VIEW_FRUSTUM_MESH_HPP
#define SFZ_GL_VIEW_FRUSTUM_MESH_HPP

#include <cstdint>>

#include "sfz/geometry/ViewFrustum.hpp"
#include "sfz/math/Matrix.hpp"
#include "sfz/math/Vector.hpp"

namespace gl {

using sfz::mat4;
using sfz::vec3;
using sfz::ViewFrustum;
using std::uint32_t;

class ViewFrustumMesh final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	ViewFrustumMesh() noexcept = default;
	ViewFrustumMesh(const ViewFrustumMesh&) = delete;
	ViewFrustumMesh& operator= (const ViewFrustumMesh&) = delete;

	ViewFrustumMesh(const ViewFrustum& viewFrustum) noexcept;
	ViewFrustumMesh(float verticalFovDeg, float aspect, float near, float far) noexcept;
	ViewFrustumMesh(ViewFrustumMesh&& other) noexcept;
	ViewFrustumMesh& operator= (ViewFrustumMesh&& other) noexcept;
	~ViewFrustumMesh() noexcept;

	// Public methods
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	void render() noexcept;
	mat4 generateTransform(const ViewFrustum& viewFrustum) const noexcept;
	mat4 generateTransform(vec3 pos, vec3 dir, vec3 up) const noexcept;

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	uint32_t mVAO = 0;
	uint32_t mPosBuffer = 0;
	uint32_t mNormalBuffer = 0;
	uint32_t mUVBuffer = 0;
	uint32_t mMaterialIDBuffer = 0;
	uint32_t mIndexBuffer = 0;
};

} // namespace gl
#endif