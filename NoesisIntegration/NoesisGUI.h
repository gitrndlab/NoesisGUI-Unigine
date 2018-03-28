/*
  NoesisGUI - Unigine Integration
  Copyright (c) 2014-2018 R&D Lab. All right reserved.
  office@researchdevelopinglab.com
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/ 

#pragma once

#include <NsApp\Display.h>
#include <NsApp/Launcher.h>
#include <NsRender/RenderContext.h>
#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UnigineTextures.h>
#include <UnigineWidgets.h>
#include <UnigineGui.h>
#include <UnigineGame.h>
#include <UnigineString.h>
#include <D3D11.h>
#include <Noesis_pch.h>

using namespace Unigine;
using namespace Noesis;
using namespace NoesisApp;

class NoesisGUI : public Base
{
public:
	NoesisGUI();
	~NoesisGUI();

	void Render();
	void Update();
	void Initialize();

	static NoesisGUI &getInstance();

	NoesisGUI &getInstanceInner();

	void Shutdown();

	Noesis::Ptr<FrameworkElement> xaml;
	Noesis::Ptr<IView> view;
	Noesis::Ptr<RenderDevice> device;

	Noesis::Ptr<NoesisApp::Display> display;
	Noesis::Ptr<NoesisApp::RenderContext> context;

	ID3D11Device* pDevice;
	ID3D11DeviceContext* pContext;

	HWND window;
	Unigine::WidgetSpritePtr hud;
	TexturePtr my_texture;

	Game *game;
	GuiPtr gui;

	std::string ui_file_name;

	void LoadUI(std::string name);
	void LoadUIbyUS(const Variable &name);

	void Clear();

	ID3D11RenderTargetView* ppOldRtv = nullptr;
	ID3D11DepthStencilView* ppOldDsv = nullptr;

	bool pressed = false;

	int width_texture;
	int height_texture;

	int width_app;
	int height_app;
};