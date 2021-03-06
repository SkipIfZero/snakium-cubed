#include "sfz/gui/ImageItem.hpp"

#include "sfz/Assert.hpp"
#include "sfz/gui/DefaultItemRenderers.hpp"

namespace gui {

// ImageItem: Renderer Factory
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

ItemRendererFactory<ImageItem> ImageItem::rendererFactory = defaultImageItemRendererFactory();

// ImageItem: Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

ImageItem::ImageItem(gl::TextureRegion imageRegion, unsigned int texture,
                     const AABB2D& imageDim, HorizontalAlign hAlign, vec2 imageScale) noexcept
:
	imageRegion{imageRegion},
	texture{texture},
	imageDim{imageDim},
	hAlign{hAlign},
	imageScale{imageScale}
{
	renderer = rendererFactory(*this);
}

ImageItem::ImageItem(const gl::Texture& texture, HorizontalAlign hAlign, vec2 imageScale) noexcept
:
	ImageItem(gl::TextureRegion(vec2(0.0f), vec2(1.0f)), texture.handle(), texture.dimensions(), hAlign, imageScale)
{ }

// ImageItem: Virtual methods overriden from BaseItem
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool ImageItem::input(vec2, vec2, sdl::ButtonState, vec2)
{
	return false;
}

KeyInput ImageItem::input(KeyInput key)
{
	return key;
}

void ImageItem::update(float delta)
{
	renderer->update(delta);
}

void ImageItem::draw(vec2 basePos, uint32_t fbo, const AABB2D& viewport, const AABB2D& cam)
{
	renderer->draw(basePos, fbo, viewport, cam);
}

// ImageItem: Virtual getters overriden from BaseItem
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool ImageItem::isSelected() const
{
	return false;
}

bool ImageItem::isEnabled() const
{
	return false;
}

// ImageItem: Virtual setters overriden from BaseItem
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void ImageItem::deselect()
{
	// Nothing to do
}

void ImageItem::enable()
{
	sfz_assert_debug(false);
}

void ImageItem::disable()
{
	sfz_assert_debug(false);
}

} // namespace gui