#pragma once

struct Pos2D
{
	short x;
	short y;
};

// 컴포넌트로 넣기엔 뭔가 영 애매하다
class Transform
{
public:
	Transform() = default;
	Transform(const Transform&) = delete;

	virtual ~Transform() = default;

	Pos2D pos;
	Pos2D scale;		// 유사 콜라이더

	virtual bool IsIntersect(int x, int y);

private:

};