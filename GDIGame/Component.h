#pragma once

class GameObjectBase;

class Component {
public:
	Component() = delete;
	Component(const Component&) = delete;
	Component(GameObjectBase* gameObject) : pObject(gameObject) { }

	virtual ~Component() = default;

	// Lifecycles ...할거 없어도 걍 호출!
	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate() = 0;

	virtual void OnDestroy() = 0;


	GameObjectBase* GetGameObject() const { return pObject; }

protected:
	GameObjectBase* pObject = nullptr;
};