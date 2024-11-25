add_library(imgui
	./imgui.cpp
	./imgui.h
	./imstb_rectpack.h
	./imstb_textedit.h
	./imstb_truetype.h
    ./imgui_demo.cpp
    ./imgui_draw.cpp
    ./imgui_internal.h
    ./imgui_tables.cpp
    ./imgui_widgets.cpp
    ./imgui_impl_sdlrenderer2.cpp
    ./imgui_impl_sdlrenderer2.h
    ./imgui_impl_sdl2.cpp
    ./imgui_impl_sdl2.h
)

target_link_libraries(imgui SDL2 SDL2main)