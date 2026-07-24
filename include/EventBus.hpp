#ifndef EVENTBUS_HPP
#define EVENTBUS_HPP

#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>

class EventBus {
public:
    EventBus() = default;
    ~EventBus() = default;

    // Deshabilitar copia
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    // Suscribirse a un evento específico T (ej. EventBus::subscribe<PlayerDiedEvent>(...))
    template <typename T>
    void subscribe(std::function<void(const T&)> callback) {
        auto type = std::type_index(typeid(T));
        
        // Empaquetamos la función callback para que acepte un puntero genérico (const void*)
        m_subscribers[type].push_back([callback](const void* eventData) {
            callback(*static_cast<const T*>(eventData));
        });
    }

    // Publicar/Emitir un evento T a todos sus suscriptores activos
    template <typename T>
    void publish(const T& event) {
        auto type = std::type_index(typeid(T));
        auto it = m_subscribers.find(type);

        if (it != m_subscribers.end()) {
            for (auto& listener : it->second) {
                listener(&event);
            }
        }
    }

    // Limpia todos los suscriptores (útil al cambiar de nivel o reiniciar)
    void clear();

private:
    using EventCallback = std::function<void(const void*)>;
    std::unordered_map<std::type_index, std::vector<EventCallback>> m_subscribers;
};

#endif // EVENTBUS_HPP