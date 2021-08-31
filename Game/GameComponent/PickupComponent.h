#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"

class PickupComponent : public nc::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PickupComponent>(*this); }

	void Create() override;
	virtual void Update() override;

	virtual void OnCollision(const nc::Event& event);

	virtual ~PickupComponent();

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;
};