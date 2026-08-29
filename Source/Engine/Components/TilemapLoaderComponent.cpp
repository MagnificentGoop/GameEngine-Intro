#include "pch.h"
#include "TilemapLoaderComponent.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Renderer/Tilemap.h"
#include "Resources/ResourceManager.h"

namespace bad {
	FACTORY_REGISTER(TilemapLoaderComponent);

	TilemapLoaderComponent::TilemapLoaderComponent(const TilemapLoaderComponent& other){
		m_tilemap = other.m_tilemap;
	}

	void bad::TilemapLoaderComponent::Start(){
		m_tilemap = Resources().Get<Tilemap>(m_tilemapName, Engine::Get().GetRenderer());
	}
	void TilemapLoaderComponent::Draw(const Renderer& renderer){
		
	}
	void TilemapLoaderComponent::Read(const json::value_t& value){
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "tilemap_name", m_tilemap);
	}
}
