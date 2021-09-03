#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"

class EnemyComponent : public nc::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<EnemyComponent>(*this); }

	void Create() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(const nc::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	float speed = 0;
};