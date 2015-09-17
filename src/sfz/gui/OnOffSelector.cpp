#include "sfz/gui/OnOffSelector.hpp"

#include "sfz/geometry/Intersection.hpp"
#include "sfz/gui/RenderingSettings.hpp"

namespace gui {

// OnOffSelector: Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

OnOffSelector::OnOffSelector(const string& text, const function<bool(void)>& checkStateFunc,
                             const function<void(void)>& changeStateFunc, float stateAlignOffset)
:
	text{text + ":"},
	checkStateFunc{checkStateFunc},
	changeStateFunc{changeStateFunc},
	stateAlignOffset{stateAlignOffset}
{ }

// OnOffSelector: Virtual methods overriden from BaseItem
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool OnOffSelector::input(vec2 basePos, vec2 pointerPos, sdl::ButtonState pointerState, vec2 wheel)
{
	if (!mEnabled) return false;
	mSelected = sfz::pointInside(bounds(basePos), pointerPos);
	if (pointerState == sdl::ButtonState::UP) {
		if (changeStateFunc) changeStateFunc();
	}
	return mSelected;
}

KeyInput OnOffSelector::input(KeyInput key)
{
	if (!mEnabled) return key;
	if (mSelected) {
		if (key == KeyInput::ACTIVATE) {
			if (changeStateFunc) changeStateFunc();
			return KeyInput::NONE;
		}
		else if (key == KeyInput::DOWN || key == KeyInput::UP) {
			mSelected = false;
			return key;
		} else if (key == KeyInput::LEFT) {
			bool state = false;
			if (checkStateFunc) state = checkStateFunc();
			if (!state && changeStateFunc) changeStateFunc();
		} else if (key == KeyInput::RIGHT) {
			bool state = false;
			if (checkStateFunc) state = checkStateFunc();
			if (state && changeStateFunc) changeStateFunc();
		}
		return KeyInput::NONE;
	} else {
		if (key == KeyInput::DOWN || key == KeyInput::UP) {
			mSelected = true;
		}
		return KeyInput::NONE;
	}
}

void OnOffSelector::update(float delta)
{
	RenderingSettings::INSTANCE().onOffSelectorRenderer->update(*this, delta);
}

void OnOffSelector::draw(vec2 basePos, uint32_t fbo, const AABB2D& viewport, const AABB2D& cam)
{
	RenderingSettings::INSTANCE().onOffSelectorRenderer->draw(*this, basePos, fbo, viewport, cam);
}

// OnOffSelector: Virtual getters overriden from BaseItem
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool OnOffSelector::isSelected() const
{
	return mSelected;
}

bool OnOffSelector::isEnabled() const
{
	return mEnabled;
}

// OnOffSelector: Virtual setters overriden from BaseItem
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void OnOffSelector::deselect()
{
	mSelected = false;
}

void OnOffSelector::enable()
{
	mEnabled = true;
}

void OnOffSelector::disable()
{
	mEnabled = false;
	mSelected = false;
}

} // namespace gui