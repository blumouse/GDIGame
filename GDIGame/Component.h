#pragma once

class GameObjectBase;

class Component {
public:
	Component() = delete;
	Component(const Component&) = delete;

	virtual ~Component() = default;

	GameObjectBase* GetGameObject() const { return pObject; }

protected:
	GameObjectBase* pObject = nullptr;
};