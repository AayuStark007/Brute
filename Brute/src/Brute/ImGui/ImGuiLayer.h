#pragma once

#include "Brute/Core/Layer.h"

#include "Brute/Events/KeyEvent.h"
#include "Brute/Events/MouseEvent.h"
#include "Brute/Events/ApplicationEvent.h"

namespace Brute {

	class BRUTE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}