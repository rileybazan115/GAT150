#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"
#include "GameComponent/ProjectileComponent.h"

void Game::Initialize()
{
	// create engine
	engine = std::make_unique<nc::Engine>();
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickupComponent);
	REGISTER_CLASS(ProjectileComponent);

	//create scene
	scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::SetFilePath("../Resources");

	engine->Get<nc::EventSystem>()->Subscribe("addScore", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();

	quit = (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed);
	scene->Update(engine->time.deltaTime);

	switch (state)
	{
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default:
		break;
	}

	auto scoreActor = scene->FindActor("Score");
	if (scoreActor)
	{
		scoreActor->GetComponent<nc::TextComponent>()->SetText(std::to_string(score));
	}
	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<nc::Renderer>()->BegineFrame();

	engine->Draw(engine->Get<nc::Renderer>());
	scene->Draw(engine->Get<nc::Renderer>());

	engine->Get<nc::Renderer>()->Endframe();
}

void Game::Reset()
{
	scene->RemoveAllActors();

	rapidjson::Document document;
	bool success = nc::json::Load("Title.txt", document);
	assert(success);
	scene->Read(document);

	state = eState::Title;
}

void Game::Title()
{
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed)
	{
		auto title = scene->FindActor("Title");
		assert(title);
		title->active = false;

		state = eState::StartGame;
	}

}

void Game::StartGame()
{
	rapidjson::Document document;
	bool success = nc::json::Load("Scene.txt", document);
	assert(success);
	scene->Read(document);

	nc::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = nc::json::Load("Map.txt", document);
	assert(success);
	tilemap.Read(document);
	tilemap.Create();

	state = eState::StartLevel;
	stateTimer = 0;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;
	if (stateTimer >= 1)
	{
		auto player = nc::ObjectFactory::Instance().Create<nc::Actor>("Player");
		player->transform.position = nc::Vector2{ 400, 450 };
		scene->AddActor(std::move(player));

		spawnTimer = 2;
		state = eState::Level;
	}
}

void Game::Level()
{
	spawnTimer -= engine->time.deltaTime;
	if (spawnTimer <= 0)
	{
		spawnTimer = nc::RandomRange(1, 2);

		auto enemy = nc::ObjectFactory::Instance().Create<nc::Actor>("Enemy");
		enemy->transform.position = nc::Vector2{ nc::RandomRange(100, 700), 150.0 };
		scene->AddActor(std::move(enemy));

		if (!scene->FindActor("Player"))
		{
			state = eState::PlayerDead;
		}
	}
}

void Game::PlayerDead()
{
	rapidjson::Document document;
	bool success = nc::json::Load("PlayerDead.txt", document);
	assert(success);
	scene->Read(document);

	spawnTimer += engine->time.deltaTime;
	if (spawnTimer >= 3)
	{
		state = eState::Reset;
	}
}

void Game::GameOver()
{

}

void Game::OnAddScore(const nc::Event& event)
{
	score += std::get<int>(event.data);
}