//#include "Player.h"
//#include "Engine.h"
//#include "Math/MathUtils.h"
//#include "Projectile.h"
//#include "Enemy.h"
//#include "Projectile.h"
//#include <memory>
//
//Player::Player(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform, texture }, speed{ speed }
//{
//
//}
//
//void Player::Initialize()
//{
//
//}
//
//void Player::Update(float dt)
//{
//	float thrust = 0;
//	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == nc::InputSystem::eKeyState::Held) { thrust = speed; }
//	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == nc::InputSystem::eKeyState::Held) { thrust = -speed; }
//	//if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == nc::InputSystem::eKeyState::Held) { thrust = speed; }
//	//if (Core::Input::IsPressed('S')) { input += pbls::Vector2::down; }
//
//	nc::Vector2 acceleration;
//	acceleration += nc::Vector2::Rotate(nc::Vector2::up, transform.rotation) * thrust;
//
//	velocity += acceleration * dt;
//
//	transform.position += velocity * dt;
//
//	velocity *= 0.98f;
//
//	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
//	//transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);
//
//	//fire
//	fireTimer -= dt;
//	if (fireTimer <= 0 && scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Held)
//	{
//		fireTimer = fireRate;
//		nc::Transform t = transform;
//		t.scale = .5f;
//
//		std::unique_ptr<Projectile> projectile = (std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/spaceMissiles_001.png", scene->engine->Get<nc::Renderer>()), 600));
//		projectile->tag = "Player";
//		scene->AddActor(std::move(projectile));
//		scene->engine->Get<nc::AudioSystem>()->PlayAudio("playerFire");
//	}
//
//	Actor::Update(dt);
//}
//
//void Player::OnCollision(Actor* actor)
//{
//	if (dynamic_cast<Enemy*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy"))
//	{
//		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 1, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle02.png"), 50);		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
//
//		nc::Event event;
//		event.name = "PlayerDead";
//		event.data = std::string("yes I'm dead!");
//		scene->engine->Get<nc::EventSystem>()->Notify(event);
//		destroy = true;
//	}
//
//	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy")
//	{
//		actor->destroy = true;
//	}
//}
