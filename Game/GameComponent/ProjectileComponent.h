#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"
#include "Math/Vector2.h"

class ProjectileComponent : public nc::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<ProjectileComponent>(*this); }

	void Create() override;
	virtual void Update() override;

	virtual void OnCollision(const nc::Event& event);

	virtual ~ProjectileComponent();

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed = 0;
	nc::Vector2 direction;

private:
	std::list<nc::Actor*> contacts;
};