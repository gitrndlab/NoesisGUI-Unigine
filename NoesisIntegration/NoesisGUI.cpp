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

#include "NoesisGUI.h"

#include <NsApp\LocalXamlProvider.h>
#include <NsApp\LocalTextureProvider.h>
#include <NsApp\LocalFontProvider.h>

#include "D3D11RenderDevice.h"

#include <UnigineApp.h>
#include <UnigineInterpreter.h>

using namespace Unigine;
using namespace Noesis;
using namespace NoesisApp;

void NoesisLogHandler(const char* filename, uint32_t line, uint32_t level, const char* channel, const char* message)
{
	if (strcmp(channel, "") == 0)
	{
		// [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
		const char* prefixes[] = { "T", "D", "I", "W", "E" };
		const char* prefix = level < NS_COUNTOF(prefixes) ? prefixes[level] : " ";
		
		Unigine::Log::message("NOESIS %s %s", prefix, message);
	}
}

NoesisGUI::NoesisGUI()
{
	width_texture = 1920;
	height_texture = 1080;

	width_app = App::get()->getWidth();
	height_app = App::get()->getHeight();
}

NoesisGUI::~NoesisGUI()
{
}

void NoesisGUI::Render()
{
	if (!view)
		return;

	ppOldRtv = nullptr;
	ppOldDsv = nullptr;
	//pContext->OMGetRenderTargets(1, &ppOldRtv, &ppOldDsv);

	ID3D11RenderTargetView* pTexNoesisRTV = static_cast<ID3D11RenderTargetView*>(my_texture->getD3D11RenderTargetView());
	pContext->OMSetRenderTargets(1, &pTexNoesisRTV, nullptr);

	view->GetRenderer()->UpdateRenderTree();
	view->GetRenderer()->RenderOffscreen();

	view->GetRenderer()->Render();
	//pContext->OMSetRenderTargets(1, &ppOldRtv, ppOldDsv);
}

void NoesisGUI::Update()
{
	if (!view)
		return;

	static uint64_t startTime = Noesis::HighResTimer::Ticks();

	uint64_t time = Noesis::HighResTimer::Ticks();
	view->Update(Noesis::HighResTimer::Seconds(time - startTime));

	// Scale mouse movement
	float diffX = (float)((float)width_texture / (float)width_app);
	float diffY = (float)((float)height_texture / (float)height_app);
	int mx = App::get()->getMouseX();
	int my = App::get()->getMouseY();
	float x = (float)mx * diffX;
	float y = (float)my * diffY;
	//int mouseX = (float)App::get()->getMouseX() * diff;
	int mouseX = (int)x;
	//int mouseY = App::get()->getMouseY();
	int mouseY = (int)y;

	view->MouseMove(mouseX, mouseY);

	if (!pressed && App::get()->getMouseButtonState(App::BUTTON_LEFT))
	{
		view->MouseButtonDown(mouseX, mouseY, MouseButton_Left);
		pressed = true;
	}
	else if (!App::get()->getMouseButtonState(App::BUTTON_LEFT))
	{
		if (pressed)
		{
			view->MouseButtonUp(mouseX, mouseY, MouseButton_Left);
			pressed = false;
		}
	}

	if (App::get()->clearKeyState('j'))
	{
		view->Char('j');
	}

	// Press F1 to reload xaml file
	if (App::get()->clearKeyState(App::KEY_F1))
	{
		Clear();
		xaml = Noesis::GUI::LoadXaml<FrameworkElement>(ui_file_name.c_str());
		view->GetRenderer()->Shutdown();
		view = Noesis::GUI::CreateView(xaml);
		view->SetSize(width_texture, height_texture);
		view->GetRenderer()->Init(device);
	}

	// Press F2 to grab mouse at GUI elements
	if (App::get()->clearKeyState(App::KEY_F2))
	{
		gui->setMouseGrab(1);
	}

	// Press F3 to release mouse from GUI
	if (App::get()->clearKeyState(App::KEY_F3))
	{
		gui->setMouseGrab(0);
	}

}

void NoesisGUI::Initialize()
{
	Noesis::GUI::Init(nullptr, NoesisLogHandler, nullptr);

	Noesis::GUI::SetXamlProvider(MakePtr<LocalXamlProvider>("."));
	Noesis::GUI::SetTextureProvider(MakePtr<LocalTextureProvider>("."));
	Noesis::GUI::SetFontProvider(MakePtr<LocalFontProvider>("."));

	pDevice = static_cast<ID3D11Device*>(Unigine::App::get()->getD3D11Device());
	pContext = nullptr;
	pDevice->GetImmediateContext(&pContext);

	device = *new NoesisApp::D3D11RenderDevice(pContext, false);
	
	gui = Unigine::Gui::get();
	hud = WidgetSprite::create(gui);
	hud->setPosition(0, 0);
	hud->setWidth(width_texture);
	hud->setHeight(height_texture);
	hud->setLayerBlendFunc(0, Unigine::Gui::BLEND_ONE, Unigine::Gui::BLEND_ONE_MINUS_SRC_ALPHA);
	gui->setTransparentEnabled(1);

	gui->addChild(hud->getWidget(), Unigine::Gui::ALIGN_OVERLAP);

	my_texture = Unigine::Texture::create();

	Clear();
	hud->setRender(my_texture);
}

NoesisGUI &NoesisGUI::getInstance()
{
	static NoesisGUI INSTANCE;
	return INSTANCE;
}

NoesisGUI & NoesisGUI::getInstanceInner()
{
	return getInstance();
}

void NoesisGUI::Shutdown()
{
	my_texture.clear();
	hud.clear();
	gui.clear();
	
	xaml.Reset();
	if (view)
	{
		view->GetRenderer()->Shutdown();
		view.Reset();
	}
	
	device.Reset();
	Noesis::GUI::Shutdown();
}

// Load xaml file by US
void NoesisGUI::LoadUIbyUS(const Variable &name)
{
	if (name.getType() == Variable::STRING ) {
		ui_file_name = name.getString();
	}
	else
	{
		Unigine::Log::error("Error load gui file");
		return;
	}

	if (view)
	{
		view->GetRenderer()->Shutdown();
	}

	Clear();

	xaml = Noesis::GUI::LoadXaml<FrameworkElement>(ui_file_name.c_str());
	
	view = Noesis::GUI::CreateView(xaml);
	view->SetSize(width_texture, height_texture);

	view->GetRenderer()->Init(device);

	gui->setMouseGrab(1);
}

// Load xaml file
void NoesisGUI::LoadUI(std::string name)
{
	ui_file_name = name;

	xaml = Noesis::GUI::LoadXaml<FrameworkElement>(ui_file_name.c_str());
	
	if (view)
	{
		view->GetRenderer()->Shutdown();
	}

	Clear();

	view = Noesis::GUI::CreateView(xaml);
	view->SetIsPPAAEnabled(true);
	view->SetTessellationQuality(TessellationQuality_High);
	view->SetSize(width_texture, height_texture);
	view->GetRenderer()->Init(device);
}

void NoesisGUI::Clear()
{
	int flags = Unigine::TextureRender::TEXTURE_COLOR | Unigine::TextureRender::COLOR_RGBA8 |
		Unigine::TextureRender::TEXTURE_DEPTH | Unigine::TextureRender::DEPTH_24S8 |
		Unigine::TextureRender::MULTISAMPLE_8 | Unigine::Texture::USAGE_RENDER;

	my_texture->create2D(width_texture, height_texture, Unigine::Texture::FORMAT_RGBA8, flags);
}
