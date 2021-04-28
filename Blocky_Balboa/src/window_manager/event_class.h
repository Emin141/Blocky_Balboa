#pragma once

class Event
{
public:
	//enum class Type {
	//	NONE = -1,
	//	CLOSE = 0,
	//	KEY_PRESS = 1,
	//	KEY_RELEASE = 2
	//};

	enum class Key {
		None = -1,
		Escape = 0,
		Q, W, E, R, T, Z, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Y, X, C, V, B, N, M,
		One, Two, Three, Four, Five, Six,
		Seven, Eight, Nine, Zero,
		Enter, Space, L_shift, L_ctrl, L_alt,
		R_alt, R_shift, R_ctrl, Backspace,
		Total_Number
	};

	//inline void setType(Type&& _type) { type = _type; }
	inline void setKey(Key&& _key) { key = _key; }

public:
	//Type type;
	Key key;

private:

};