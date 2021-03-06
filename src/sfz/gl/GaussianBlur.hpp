#pragma once
#ifndef SFZ_GL_GAUSSIAN_BLUR_HPP
#define SFZ_GL_GAUSSIAN_BLUR_HPP

#include <cstdint>
#include <memory>

#include <sfz/gl/Framebuffer.hpp>
#include <sfz/gl/PostProcessQuad.hpp>
#include <sfz/gl/Program.hpp>
#include <sfz/math/Vector.hpp>

namespace gl {

using sfz::vec2i;
using std::int32_t;
using std::uint32_t;
using std::unique_ptr;

// Gaussian blur class
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

/**
 * @brief A class holding a shader and framebuffer for calculating gaussian blur
 *
 * The size of the blur is controlled by two parameters, radius and sigma. Sigma is the standard
 * deviation of the gaussian blur kernel (in pixels) while radius is the amount of pixels to
 * sample in each direction (i.e. a radius of 2 would result in 5 pixel samples). The gaussian
 * kernel is normalized so that the total weight of all samples equal to 1.
 *
 * If the interpolated samples mode is enabled the shader will sample two pixels at once using
 * linear interpolation. Basically equal to the following formula: (w1 + w2) * ((p1 + p2)/2).
 * This will of course introduce a slight error to the blur kernel, but it is much faster.
 */
class GaussianBlur final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	GaussianBlur() = default;
	GaussianBlur(const GaussianBlur&) = delete;
	GaussianBlur& operator= (const GaussianBlur&) = delete;
	
	GaussianBlur(vec2i dimensions, int32_t radius, float sigma, bool interpolatedSamples = true) noexcept;
	
	GaussianBlur(GaussianBlur&& other) noexcept;
	GaussianBlur& operator= (GaussianBlur&& other) noexcept;
	~GaussianBlur() noexcept;

	// Public methods
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Applies the gaussian blur filter to the texture and writes it to the specifed fbo
	 * @param srcDimensions the dimensions of the texture, needs to be same as the internal
	 *                      resolution of this BoxBlur object.
	 */
	void apply(uint32_t dstFBO, uint32_t srcTexture, vec2i srcDimensions) noexcept;

	/**
	* @brief Applies the gaussian blur filter to the texture and writes it to the specifed fbo
	* @param radius the amount of pixels to sample in a direction (pixels sampled = 2*radius + 1)
	* @param interpolatedSamples a flag used to determine if interpolated sampling should be used
	*                            or not, see class documentation.
	*/
	bool setBlurParams(int32_t radius, float sigma, bool interpolatedSamples = true) noexcept;

	// Getters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline int32_t radius() const noexcept { return mRadius; }
	inline float sigma() const noexcept { return mSigma; }
	inline const float* samples() const noexcept { return &mSamples[0]; }

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	Program mHorizontalBlurProgram, mVerticalBlurProgram,
	        mHorizontalBlurInterpolatedProgram, mVerticalBlurInterpolatedProgram;
	Framebuffer mTempFB;
	PostProcessQuad mPostProcessQuad;
	uint32_t mSamplerObject = 0;

	int32_t mRadius = -1;
	float mSigma = 1.0f;
	unique_ptr<float[]> mSamples;
	bool mInterpolatedSamples = false;
};

} // namespace sfz
#endif