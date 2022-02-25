
/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef DEBUGNOTIFICATION_HPP
#define DEBUGNOTIFICATION_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API DebugNotification {
    private:
        static constexpr const char* TheShortName = "DebugNotification";
        static constexpr const char* TheLongName = "DebugNotification";

    public:
        inline static int32_t ID() {
            return 11;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        DebugNotification() = default;
        DebugNotification(const DebugNotification&) = default;
        DebugNotification& operator=(const DebugNotification&) = default;
        DebugNotification(DebugNotification&&) = default;
        DebugNotification& operator=(DebugNotification&&) = default;
        ~DebugNotification() = default;

    public:
        inline DebugNotification& msg(const std::string &v) noexcept {
            m_msg = v;
            return *this;
        }
        inline std::string msg() const noexcept {
            return m_msg;
        }
        inline DebugNotification& uuid(const uint16_t &v) noexcept {
            m_uuid = v;
            return *this;
        }
        inline uint16_t uuid() const noexcept {
            return m_uuid;
        }
        inline DebugNotification& category(const std::string &v) noexcept {
            m_category = v;
            return *this;
        }
        inline std::string category() const noexcept {
            return m_category;
        }
        inline DebugNotification& source(const std::string &v) noexcept {
            m_source = v;
            return *this;
        }
        inline std::string source() const noexcept {
            return m_source;
        }
        inline DebugNotification& raised(const std::string &v) noexcept {
            m_raised = v;
            return *this;
        }
        inline std::string raised() const noexcept {
            return m_raised;
        }
        inline DebugNotification& acknowledged(const std::string &v) noexcept {
            m_acknowledged = v;
            return *this;
        }
        inline std::string acknowledged() const noexcept {
            return m_acknowledged;
        }
        inline DebugNotification& cancelled(const std::string &v) noexcept {
            m_cancelled = v;
            return *this;
        }
        inline std::string cancelled() const noexcept {
            return m_cancelled;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
                return;
            }
            if (2 == fieldId) {
                doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
                return;
            }
            if (3 == fieldId) {
                doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
                return;
            }
            if (4 == fieldId) {
                doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
                return;
            }
            if (5 == fieldId) {
                doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
                return;
            }
            if (6 == fieldId) {
                doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
                return;
            }
            if (7 == fieldId) {
                doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
            doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
            doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
            doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
            doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
            doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
            doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, preVisit, visit, postVisit);
            doTripletForwardVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, preVisit, visit, postVisit);
            doTripletForwardVisit(3, std::move("std::string"s), std::move("category"s), m_category, preVisit, visit, postVisit);
            doTripletForwardVisit(4, std::move("std::string"s), std::move("source"s), m_source, preVisit, visit, postVisit);
            doTripletForwardVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, preVisit, visit, postVisit);
            doTripletForwardVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, preVisit, visit, postVisit);
            doTripletForwardVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        std::string m_msg{ ""s }; // field identifier = 1.
        uint16_t m_uuid{ 0 }; // field identifier = 2.
        std::string m_category{ ""s }; // field identifier = 3.
        std::string m_source{ ""s }; // field identifier = 4.
        std::string m_raised{ ""s }; // field identifier = 5.
        std::string m_acknowledged{ ""s }; // field identifier = 6.
        std::string m_cancelled{ ""s }; // field identifier = 7.
};


template<>
struct isVisitable<DebugNotification> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<DebugNotification> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef INFONOTIFICATION_HPP
#define INFONOTIFICATION_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API InfoNotification {
    private:
        static constexpr const char* TheShortName = "InfoNotification";
        static constexpr const char* TheLongName = "InfoNotification";

    public:
        inline static int32_t ID() {
            return 12;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        InfoNotification() = default;
        InfoNotification(const InfoNotification&) = default;
        InfoNotification& operator=(const InfoNotification&) = default;
        InfoNotification(InfoNotification&&) = default;
        InfoNotification& operator=(InfoNotification&&) = default;
        ~InfoNotification() = default;

    public:
        inline InfoNotification& msg(const std::string &v) noexcept {
            m_msg = v;
            return *this;
        }
        inline std::string msg() const noexcept {
            return m_msg;
        }
        inline InfoNotification& uuid(const uint16_t &v) noexcept {
            m_uuid = v;
            return *this;
        }
        inline uint16_t uuid() const noexcept {
            return m_uuid;
        }
        inline InfoNotification& category(const std::string &v) noexcept {
            m_category = v;
            return *this;
        }
        inline std::string category() const noexcept {
            return m_category;
        }
        inline InfoNotification& source(const std::string &v) noexcept {
            m_source = v;
            return *this;
        }
        inline std::string source() const noexcept {
            return m_source;
        }
        inline InfoNotification& raised(const std::string &v) noexcept {
            m_raised = v;
            return *this;
        }
        inline std::string raised() const noexcept {
            return m_raised;
        }
        inline InfoNotification& acknowledged(const std::string &v) noexcept {
            m_acknowledged = v;
            return *this;
        }
        inline std::string acknowledged() const noexcept {
            return m_acknowledged;
        }
        inline InfoNotification& cancelled(const std::string &v) noexcept {
            m_cancelled = v;
            return *this;
        }
        inline std::string cancelled() const noexcept {
            return m_cancelled;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
                return;
            }
            if (2 == fieldId) {
                doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
                return;
            }
            if (3 == fieldId) {
                doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
                return;
            }
            if (4 == fieldId) {
                doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
                return;
            }
            if (5 == fieldId) {
                doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
                return;
            }
            if (6 == fieldId) {
                doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
                return;
            }
            if (7 == fieldId) {
                doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
            doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
            doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
            doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
            doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
            doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
            doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, preVisit, visit, postVisit);
            doTripletForwardVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, preVisit, visit, postVisit);
            doTripletForwardVisit(3, std::move("std::string"s), std::move("category"s), m_category, preVisit, visit, postVisit);
            doTripletForwardVisit(4, std::move("std::string"s), std::move("source"s), m_source, preVisit, visit, postVisit);
            doTripletForwardVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, preVisit, visit, postVisit);
            doTripletForwardVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, preVisit, visit, postVisit);
            doTripletForwardVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        std::string m_msg{ ""s }; // field identifier = 1.
        uint16_t m_uuid{ 0 }; // field identifier = 2.
        std::string m_category{ ""s }; // field identifier = 3.
        std::string m_source{ ""s }; // field identifier = 4.
        std::string m_raised{ ""s }; // field identifier = 5.
        std::string m_acknowledged{ ""s }; // field identifier = 6.
        std::string m_cancelled{ ""s }; // field identifier = 7.
};


template<>
struct isVisitable<InfoNotification> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<InfoNotification> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef CAUTIONNOTIFICATION_HPP
#define CAUTIONNOTIFICATION_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API CautionNotification {
    private:
        static constexpr const char* TheShortName = "CautionNotification";
        static constexpr const char* TheLongName = "CautionNotification";

    public:
        inline static int32_t ID() {
            return 13;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        CautionNotification() = default;
        CautionNotification(const CautionNotification&) = default;
        CautionNotification& operator=(const CautionNotification&) = default;
        CautionNotification(CautionNotification&&) = default;
        CautionNotification& operator=(CautionNotification&&) = default;
        ~CautionNotification() = default;

    public:
        inline CautionNotification& msg(const std::string &v) noexcept {
            m_msg = v;
            return *this;
        }
        inline std::string msg() const noexcept {
            return m_msg;
        }
        inline CautionNotification& uuid(const uint16_t &v) noexcept {
            m_uuid = v;
            return *this;
        }
        inline uint16_t uuid() const noexcept {
            return m_uuid;
        }
        inline CautionNotification& category(const std::string &v) noexcept {
            m_category = v;
            return *this;
        }
        inline std::string category() const noexcept {
            return m_category;
        }
        inline CautionNotification& source(const std::string &v) noexcept {
            m_source = v;
            return *this;
        }
        inline std::string source() const noexcept {
            return m_source;
        }
        inline CautionNotification& raised(const std::string &v) noexcept {
            m_raised = v;
            return *this;
        }
        inline std::string raised() const noexcept {
            return m_raised;
        }
        inline CautionNotification& acknowledged(const std::string &v) noexcept {
            m_acknowledged = v;
            return *this;
        }
        inline std::string acknowledged() const noexcept {
            return m_acknowledged;
        }
        inline CautionNotification& cancelled(const std::string &v) noexcept {
            m_cancelled = v;
            return *this;
        }
        inline std::string cancelled() const noexcept {
            return m_cancelled;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
                return;
            }
            if (2 == fieldId) {
                doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
                return;
            }
            if (3 == fieldId) {
                doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
                return;
            }
            if (4 == fieldId) {
                doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
                return;
            }
            if (5 == fieldId) {
                doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
                return;
            }
            if (6 == fieldId) {
                doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
                return;
            }
            if (7 == fieldId) {
                doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
            doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
            doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
            doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
            doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
            doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
            doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, preVisit, visit, postVisit);
            doTripletForwardVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, preVisit, visit, postVisit);
            doTripletForwardVisit(3, std::move("std::string"s), std::move("category"s), m_category, preVisit, visit, postVisit);
            doTripletForwardVisit(4, std::move("std::string"s), std::move("source"s), m_source, preVisit, visit, postVisit);
            doTripletForwardVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, preVisit, visit, postVisit);
            doTripletForwardVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, preVisit, visit, postVisit);
            doTripletForwardVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        std::string m_msg{ ""s }; // field identifier = 1.
        uint16_t m_uuid{ 0 }; // field identifier = 2.
        std::string m_category{ ""s }; // field identifier = 3.
        std::string m_source{ ""s }; // field identifier = 4.
        std::string m_raised{ ""s }; // field identifier = 5.
        std::string m_acknowledged{ ""s }; // field identifier = 6.
        std::string m_cancelled{ ""s }; // field identifier = 7.
};


template<>
struct isVisitable<CautionNotification> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<CautionNotification> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef WARNINGNOTIFICATION_HPP
#define WARNINGNOTIFICATION_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API WarningNotification {
    private:
        static constexpr const char* TheShortName = "WarningNotification";
        static constexpr const char* TheLongName = "WarningNotification";

    public:
        inline static int32_t ID() {
            return 14;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        WarningNotification() = default;
        WarningNotification(const WarningNotification&) = default;
        WarningNotification& operator=(const WarningNotification&) = default;
        WarningNotification(WarningNotification&&) = default;
        WarningNotification& operator=(WarningNotification&&) = default;
        ~WarningNotification() = default;

    public:
        inline WarningNotification& msg(const std::string &v) noexcept {
            m_msg = v;
            return *this;
        }
        inline std::string msg() const noexcept {
            return m_msg;
        }
        inline WarningNotification& uuid(const uint16_t &v) noexcept {
            m_uuid = v;
            return *this;
        }
        inline uint16_t uuid() const noexcept {
            return m_uuid;
        }
        inline WarningNotification& category(const std::string &v) noexcept {
            m_category = v;
            return *this;
        }
        inline std::string category() const noexcept {
            return m_category;
        }
        inline WarningNotification& source(const std::string &v) noexcept {
            m_source = v;
            return *this;
        }
        inline std::string source() const noexcept {
            return m_source;
        }
        inline WarningNotification& raised(const std::string &v) noexcept {
            m_raised = v;
            return *this;
        }
        inline std::string raised() const noexcept {
            return m_raised;
        }
        inline WarningNotification& acknowledged(const std::string &v) noexcept {
            m_acknowledged = v;
            return *this;
        }
        inline std::string acknowledged() const noexcept {
            return m_acknowledged;
        }
        inline WarningNotification& cancelled(const std::string &v) noexcept {
            m_cancelled = v;
            return *this;
        }
        inline std::string cancelled() const noexcept {
            return m_cancelled;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
                return;
            }
            if (2 == fieldId) {
                doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
                return;
            }
            if (3 == fieldId) {
                doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
                return;
            }
            if (4 == fieldId) {
                doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
                return;
            }
            if (5 == fieldId) {
                doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
                return;
            }
            if (6 == fieldId) {
                doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
                return;
            }
            if (7 == fieldId) {
                doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
            doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
            doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
            doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
            doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
            doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
            doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, preVisit, visit, postVisit);
            doTripletForwardVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, preVisit, visit, postVisit);
            doTripletForwardVisit(3, std::move("std::string"s), std::move("category"s), m_category, preVisit, visit, postVisit);
            doTripletForwardVisit(4, std::move("std::string"s), std::move("source"s), m_source, preVisit, visit, postVisit);
            doTripletForwardVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, preVisit, visit, postVisit);
            doTripletForwardVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, preVisit, visit, postVisit);
            doTripletForwardVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        std::string m_msg{ ""s }; // field identifier = 1.
        uint16_t m_uuid{ 0 }; // field identifier = 2.
        std::string m_category{ ""s }; // field identifier = 3.
        std::string m_source{ ""s }; // field identifier = 4.
        std::string m_raised{ ""s }; // field identifier = 5.
        std::string m_acknowledged{ ""s }; // field identifier = 6.
        std::string m_cancelled{ ""s }; // field identifier = 7.
};


template<>
struct isVisitable<WarningNotification> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<WarningNotification> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef ALARMNOTIFICATION_HPP
#define ALARMNOTIFICATION_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API AlarmNotification {
    private:
        static constexpr const char* TheShortName = "AlarmNotification";
        static constexpr const char* TheLongName = "AlarmNotification";

    public:
        inline static int32_t ID() {
            return 15;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        AlarmNotification() = default;
        AlarmNotification(const AlarmNotification&) = default;
        AlarmNotification& operator=(const AlarmNotification&) = default;
        AlarmNotification(AlarmNotification&&) = default;
        AlarmNotification& operator=(AlarmNotification&&) = default;
        ~AlarmNotification() = default;

    public:
        inline AlarmNotification& msg(const std::string &v) noexcept {
            m_msg = v;
            return *this;
        }
        inline std::string msg() const noexcept {
            return m_msg;
        }
        inline AlarmNotification& uuid(const uint16_t &v) noexcept {
            m_uuid = v;
            return *this;
        }
        inline uint16_t uuid() const noexcept {
            return m_uuid;
        }
        inline AlarmNotification& category(const std::string &v) noexcept {
            m_category = v;
            return *this;
        }
        inline std::string category() const noexcept {
            return m_category;
        }
        inline AlarmNotification& source(const std::string &v) noexcept {
            m_source = v;
            return *this;
        }
        inline std::string source() const noexcept {
            return m_source;
        }
        inline AlarmNotification& raised(const std::string &v) noexcept {
            m_raised = v;
            return *this;
        }
        inline std::string raised() const noexcept {
            return m_raised;
        }
        inline AlarmNotification& acknowledged(const std::string &v) noexcept {
            m_acknowledged = v;
            return *this;
        }
        inline std::string acknowledged() const noexcept {
            return m_acknowledged;
        }
        inline AlarmNotification& cancelled(const std::string &v) noexcept {
            m_cancelled = v;
            return *this;
        }
        inline std::string cancelled() const noexcept {
            return m_cancelled;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
                return;
            }
            if (2 == fieldId) {
                doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
                return;
            }
            if (3 == fieldId) {
                doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
                return;
            }
            if (4 == fieldId) {
                doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
                return;
            }
            if (5 == fieldId) {
                doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
                return;
            }
            if (6 == fieldId) {
                doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
                return;
            }
            if (7 == fieldId) {
                doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
            doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
            doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
            doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
            doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
            doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
            doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, preVisit, visit, postVisit);
            doTripletForwardVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, preVisit, visit, postVisit);
            doTripletForwardVisit(3, std::move("std::string"s), std::move("category"s), m_category, preVisit, visit, postVisit);
            doTripletForwardVisit(4, std::move("std::string"s), std::move("source"s), m_source, preVisit, visit, postVisit);
            doTripletForwardVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, preVisit, visit, postVisit);
            doTripletForwardVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, preVisit, visit, postVisit);
            doTripletForwardVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        std::string m_msg{ ""s }; // field identifier = 1.
        uint16_t m_uuid{ 0 }; // field identifier = 2.
        std::string m_category{ ""s }; // field identifier = 3.
        std::string m_source{ ""s }; // field identifier = 4.
        std::string m_raised{ ""s }; // field identifier = 5.
        std::string m_acknowledged{ ""s }; // field identifier = 6.
        std::string m_cancelled{ ""s }; // field identifier = 7.
};


template<>
struct isVisitable<AlarmNotification> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<AlarmNotification> {
    static const bool value = true;
};
#endif


/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef VISITABLE_TYPE_TRAIT
#define VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct visitorSelector {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct visitorSelector<true> {
    template<typename T, class Visitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
        visitor.visit(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<typename T>
struct isVisitable {
    static const bool value = false;
};

template<typename T, class Visitor>
void doVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, Visitor &visitor) {
    visitorSelector<isVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, visitor);
}
#endif

#ifndef TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#define TRIPLET_FORWARD_VISITABLE_TYPE_TRAIT
#include <cstdint>
#include <string>
#include <utility>

template<bool b>
struct tripletForwardVisitorSelector {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)preVisit;
        (void)postVisit;
        std::forward<Visitor>(visit)(fieldIdentifier, std::move(typeName), std::move(name), value);
    }
};

template<>
struct tripletForwardVisitorSelector<true> {
    template<typename T, class PreVisitor, class Visitor, class PostVisitor>
    static void impl(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
        (void)fieldIdentifier;
        (void)typeName;
        (void)name;
        // Apply preVisit, visit, and postVisit on value.
        value.accept(preVisit, visit, postVisit);
    }
};

template<typename T>
struct isTripletForwardVisitable {
    static const bool value = false;
};

template< typename T, class PreVisitor, class Visitor, class PostVisitor>
void doTripletForwardVisit(uint32_t fieldIdentifier, std::string &&typeName, std::string &&name, T &value, PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
    tripletForwardVisitorSelector<isTripletForwardVisitable<T>::value >::impl(fieldIdentifier, std::move(typeName), std::move(name), value, std::move(preVisit), std::move(visit), std::move(postVisit)); // NOLINT
}
#endif


#ifndef EMERGENCYNOTIFICATION_HPP
#define EMERGENCYNOTIFICATION_HPP

#ifdef WIN32
    // Export symbols if compile flags "LIB_SHARED" and "LIB_EXPORTS" are set on Windows.
    #ifdef LIB_SHARED
        #ifdef LIB_EXPORTS
            #define LIB_API __declspec(dllexport)
        #else
            #define LIB_API __declspec(dllimport)
        #endif
    #else
        // Disable definition if linking statically.
        #define LIB_API
    #endif
#else
    // Disable definition for non-Win32 systems.
    #define LIB_API
#endif

#include <string>
#include <utility>

using namespace std::string_literals; // NOLINT
class LIB_API EmergencyNotification {
    private:
        static constexpr const char* TheShortName = "EmergencyNotification";
        static constexpr const char* TheLongName = "EmergencyNotification";

    public:
        inline static int32_t ID() {
            return 16;
        }
        inline static const std::string ShortName() {
            return TheShortName;
        }
        inline static const std::string LongName() {
            return TheLongName;
        }

    public:
        EmergencyNotification() = default;
        EmergencyNotification(const EmergencyNotification&) = default;
        EmergencyNotification& operator=(const EmergencyNotification&) = default;
        EmergencyNotification(EmergencyNotification&&) = default;
        EmergencyNotification& operator=(EmergencyNotification&&) = default;
        ~EmergencyNotification() = default;

    public:
        inline EmergencyNotification& msg(const std::string &v) noexcept {
            m_msg = v;
            return *this;
        }
        inline std::string msg() const noexcept {
            return m_msg;
        }
        inline EmergencyNotification& uuid(const uint16_t &v) noexcept {
            m_uuid = v;
            return *this;
        }
        inline uint16_t uuid() const noexcept {
            return m_uuid;
        }
        inline EmergencyNotification& category(const std::string &v) noexcept {
            m_category = v;
            return *this;
        }
        inline std::string category() const noexcept {
            return m_category;
        }
        inline EmergencyNotification& source(const std::string &v) noexcept {
            m_source = v;
            return *this;
        }
        inline std::string source() const noexcept {
            return m_source;
        }
        inline EmergencyNotification& raised(const std::string &v) noexcept {
            m_raised = v;
            return *this;
        }
        inline std::string raised() const noexcept {
            return m_raised;
        }
        inline EmergencyNotification& acknowledged(const std::string &v) noexcept {
            m_acknowledged = v;
            return *this;
        }
        inline std::string acknowledged() const noexcept {
            return m_acknowledged;
        }
        inline EmergencyNotification& cancelled(const std::string &v) noexcept {
            m_cancelled = v;
            return *this;
        }
        inline std::string cancelled() const noexcept {
            return m_cancelled;
        }

    public:
        template<class Visitor>
        inline void accept(uint32_t fieldId, Visitor &visitor) {
            (void)fieldId;
            (void)visitor;
//            visitor.preVisit(ID(), ShortName(), LongName());
            if (1 == fieldId) {
                doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
                return;
            }
            if (2 == fieldId) {
                doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
                return;
            }
            if (3 == fieldId) {
                doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
                return;
            }
            if (4 == fieldId) {
                doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
                return;
            }
            if (5 == fieldId) {
                doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
                return;
            }
            if (6 == fieldId) {
                doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
                return;
            }
            if (7 == fieldId) {
                doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
                return;
            }
//            visitor.postVisit();
        }

        template<class Visitor>
        inline void accept(Visitor &visitor) {
            visitor.preVisit(ID(), ShortName(), LongName());
            doVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, visitor);
            doVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, visitor);
            doVisit(3, std::move("std::string"s), std::move("category"s), m_category, visitor);
            doVisit(4, std::move("std::string"s), std::move("source"s), m_source, visitor);
            doVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, visitor);
            doVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, visitor);
            doVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, visitor);
            visitor.postVisit();
        }

        template<class PreVisitor, class Visitor, class PostVisitor>
        inline void accept(PreVisitor &&preVisit, Visitor &&visit, PostVisitor &&postVisit) {
            (void)visit; // Prevent warnings from empty messages.
            std::forward<PreVisitor>(preVisit)(ID(), ShortName(), LongName());
            doTripletForwardVisit(1, std::move("std::string"s), std::move("msg"s), m_msg, preVisit, visit, postVisit);
            doTripletForwardVisit(2, std::move("uint16_t"s), std::move("uuid"s), m_uuid, preVisit, visit, postVisit);
            doTripletForwardVisit(3, std::move("std::string"s), std::move("category"s), m_category, preVisit, visit, postVisit);
            doTripletForwardVisit(4, std::move("std::string"s), std::move("source"s), m_source, preVisit, visit, postVisit);
            doTripletForwardVisit(5, std::move("std::string"s), std::move("raised"s), m_raised, preVisit, visit, postVisit);
            doTripletForwardVisit(6, std::move("std::string"s), std::move("acknowledged"s), m_acknowledged, preVisit, visit, postVisit);
            doTripletForwardVisit(7, std::move("std::string"s), std::move("cancelled"s), m_cancelled, preVisit, visit, postVisit);
            std::forward<PostVisitor>(postVisit)();
        }

    private:
        std::string m_msg{ ""s }; // field identifier = 1.
        uint16_t m_uuid{ 0 }; // field identifier = 2.
        std::string m_category{ ""s }; // field identifier = 3.
        std::string m_source{ ""s }; // field identifier = 4.
        std::string m_raised{ ""s }; // field identifier = 5.
        std::string m_acknowledged{ ""s }; // field identifier = 6.
        std::string m_cancelled{ ""s }; // field identifier = 7.
};


template<>
struct isVisitable<EmergencyNotification> {
    static const bool value = true;
};
template<>
struct isTripletForwardVisitable<EmergencyNotification> {
    static const bool value = true;
};
#endif

