//#include "Projectile.h"
//#include "Math/MathUtils.h"
//#include "Engine.h"
//
//void Projectile::Update(float dt)
//{
//	lifetime -= dt;
//	destroy = (lifetime <= 0);
//
//	transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
//	//transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
//	//transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);
//
//	//std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::blue };
//	//scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 0.5f, std::shared_ptr<nc::Texture>(), 10);
//
//	Actor::Update(dt);
//}