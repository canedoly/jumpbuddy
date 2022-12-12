#pragma once

namespace settings
{
	//removes view punch and shake
	inline bool clear_view{ true };

	//overrides game's fov with a custom value (no limit)
	inline int custom_fov{ 110 };

	//enables very fast control point capturing
	inline bool instant_capture{ true };

	//enables very fast respawn (removes death as well)
	inline bool instant_respawn{ true };

	//removes self damage from explosions and falling
	inline bool no_damage{ true };

	//removes radial damage indicator
	inline bool no_damage_indicator{ true };

	//removes pain and death sounds
	inline bool no_pain_sounds{ true };

	//removes the ressuply sound
	inline bool no_resupply_sound{ true };
}