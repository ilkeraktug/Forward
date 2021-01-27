#include "fwpch.h"
#include "LayerStack.h"


namespace Forward {
	LayerStack::LayerStack()
	{

	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerStackIndex, layer);
		m_LayerStackIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		layer->OnDetach();
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerStackIndex, layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerStackIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		overlay->OnDetach();
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerStackIndex, overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}