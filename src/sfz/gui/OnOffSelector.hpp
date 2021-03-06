#pragma once
#ifndef SFZ_GUI_ON_OFF_SELECTOR_HPP
#define SFZ_GUI_ON_OFF_SELECTOR_HPP

#include <functional>
#include <string>

#include "sfz/gui/BaseItem.hpp"

namespace gui {

using std::function;
using std::string;

/**
 * @brief A menu item for enabling or disabling an option
 */
class OnOffSelector final : public BaseItem {
public:
	// Renderer Factory (by default the default renderer)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	static ItemRendererFactory<OnOffSelector> rendererFactory;

	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	OnOffSelector() = default;
	OnOffSelector(const OnOffSelector&) = default;
	OnOffSelector& operator= (const OnOffSelector&) = default;

	/**
	 * @param text the name of the option
	 * @param checkStateFunc a function which should return whether the option is currently active
	 * @param changeStateFunc a function which should switch the active state of the option
	 * @param stateAlignOffset an offset to align the on/off strings against
	 */
	OnOffSelector(const string& text, const function<bool(void)>& checkStateFunc,
	              const function<void(void)>& changeStateFunc, float stateAlignOffset = 0.0f);

	// Constructor functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Creates a OnOffSelector using a bool pointer
	 * @param valuePtr the pointer to the value (for both reading and writing)
	 */
	static OnOffSelector* createSimple(const string& text, bool* valuePtr, float stateAlignOffset = 0.0f);

	// Virtual methods overriden from BaseItem
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	virtual bool input(vec2 basePos, vec2 pointerPos, sdl::ButtonState pointerState, vec2 wheel) override final;
	virtual KeyInput input(KeyInput key) override final;
	virtual void update(float delta) override final;
	virtual void draw(vec2 basePos, uint32_t fbo, const AABB2D& viewport, const AABB2D& cam) override final;

	// Virtual getters overriden from BaseItem
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	virtual bool isSelected() const override final;
	virtual bool isEnabled() const override final;

	// Virtual setters overriden from BaseItem
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	virtual void deselect() override final;
	virtual void enable() override final;
	virtual void disable() override final;

	// Public members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	string text;
	function<bool(void)> checkStateFunc;
	function<void(void)> changeStateFunc;
	float stateAlignOffset;

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	bool mSelected = false;
	bool mEnabled = true;
};

} // namespace gui
#endif