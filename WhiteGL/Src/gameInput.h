#pragma once

namespace Input
{
	enum class Key :int
	{
		DPAD_UP = 0,
		DPAD_DOWN = 1,
		DPAD_LEFT = 2,
		DPAD_RIGHT = 3,
		START = 4,
		A = 5,
		B = 6,
		X = 7,
		Y = 8,
		L = 9,
		R = 10,
		Z = 11,
		S = 12,
		D = 13,
		L_SHIFT,
		SPACE,
		GameEnd,
	};
	class CGameInput
	{
	private:
		bool m_keytype[(int)Key::GameEnd] = {};
	public:

		

		void setOnKey(Key keytype, bool keybool)
		{
			m_keytype[(int)keytype] = keybool;
		}

		bool getOnKey(Key keytype)
		{
			return m_keytype[(int)keytype];
		}
		float getRightAxis()
		{

		}

	};
}