# NoesisGUI-Unigine
NoesisGUI - Unigine integration library allows you to use NoesisGUI 2.1 in Unigine 2.6.1.1 engines (from Starter version).

The library is under development and cover just base integration NoesisGUI into Unigine engine.

NoesisIntegration is a library project which you integrate with your C++ Unigine project. A sample of integration you will find in UnigineIntegration folder (you can integrate it in main.cpp or in AppSystemLogic file to work with Editor2). There is also sample of integration with Unigine Script within us_world.cpp file. 

Provided integration works well only within main.cpp. To work in AppSystemLogic you have to move pContext->OMSetRenderTargets line from render() at the top of the render() function. Then it will works in Editor2 as well but it will be broken transparency, etc. Also then NoesisGUI will be below Unigine GUI layer.

You should be aware that not everything may be working yet and some of things are hardcoded as size of provided GUI textures, etc.

To work you need to download and add NoesisGUI depedencies from https://www.noesisengine.com.

# Noesis License
  D3D11RenderDevice.h, D3D11RenderDevice.cpp, Render.D3D11RenderDevice.cpp and Shaders.h files are licensed under Noesis Technologies S.L.   license where All Rights are Reserved. You can check NoesisGUI license at https://www.noesisengine.com.

# License for NoesisGUI-Unigine Integration library
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
