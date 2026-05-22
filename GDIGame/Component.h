#pragma once

class GameObjectBase;

class Component {
public:
	Component();
	~Component();

	GameObjectBase* GetObject();

private:
	GameObjectBase* pObject = nullptr;
};