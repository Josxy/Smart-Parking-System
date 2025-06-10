//
// Generated file, do not edit! Created by opp_msgtool 6.0 from ../src/SmartParkingMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "SmartParkingMessages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(VehicleArrival)

VehicleArrival::VehicleArrival(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

VehicleArrival::VehicleArrival(const VehicleArrival& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

VehicleArrival::~VehicleArrival()
{
}

VehicleArrival& VehicleArrival::operator=(const VehicleArrival& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VehicleArrival::copy(const VehicleArrival& other)
{
    this->vehicleId = other.vehicleId;
    this->arrivalTime = other.arrivalTime;
}

void VehicleArrival::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->vehicleId);
    doParsimPacking(b,this->arrivalTime);
}

void VehicleArrival::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->vehicleId);
    doParsimUnpacking(b,this->arrivalTime);
}

int VehicleArrival::getVehicleId() const
{
    return this->vehicleId;
}

void VehicleArrival::setVehicleId(int vehicleId)
{
    this->vehicleId = vehicleId;
}

omnetpp::simtime_t VehicleArrival::getArrivalTime() const
{
    return this->arrivalTime;
}

void VehicleArrival::setArrivalTime(omnetpp::simtime_t arrivalTime)
{
    this->arrivalTime = arrivalTime;
}

class VehicleArrivalDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_vehicleId,
        FIELD_arrivalTime,
    };
  public:
    VehicleArrivalDescriptor();
    virtual ~VehicleArrivalDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VehicleArrivalDescriptor)

VehicleArrivalDescriptor::VehicleArrivalDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VehicleArrival)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

VehicleArrivalDescriptor::~VehicleArrivalDescriptor()
{
    delete[] propertyNames;
}

bool VehicleArrivalDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VehicleArrival *>(obj)!=nullptr;
}

const char **VehicleArrivalDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VehicleArrivalDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VehicleArrivalDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int VehicleArrivalDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_vehicleId
        FD_ISEDITABLE,    // FIELD_arrivalTime
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *VehicleArrivalDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vehicleId",
        "arrivalTime",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int VehicleArrivalDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vehicleId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "arrivalTime") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *VehicleArrivalDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_vehicleId
        "omnetpp::simtime_t",    // FIELD_arrivalTime
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **VehicleArrivalDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VehicleArrivalDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VehicleArrivalDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VehicleArrivalDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VehicleArrival'", field);
    }
}

const char *VehicleArrivalDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VehicleArrivalDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: return long2string(pp->getVehicleId());
        case FIELD_arrivalTime: return simtime2string(pp->getArrivalTime());
        default: return "";
    }
}

void VehicleArrivalDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId(string2long(value)); break;
        case FIELD_arrivalTime: pp->setArrivalTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleArrival'", field);
    }
}

omnetpp::cValue VehicleArrivalDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: return pp->getVehicleId();
        case FIELD_arrivalTime: return pp->getArrivalTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VehicleArrival' as cValue -- field index out of range?", field);
    }
}

void VehicleArrivalDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_arrivalTime: pp->setArrivalTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleArrival'", field);
    }
}

const char *VehicleArrivalDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VehicleArrivalDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VehicleArrivalDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleArrival *pp = omnetpp::fromAnyPtr<VehicleArrival>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleArrival'", field);
    }
}

Register_Class(VehicleDeparture)

VehicleDeparture::VehicleDeparture(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

VehicleDeparture::VehicleDeparture(const VehicleDeparture& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

VehicleDeparture::~VehicleDeparture()
{
}

VehicleDeparture& VehicleDeparture::operator=(const VehicleDeparture& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VehicleDeparture::copy(const VehicleDeparture& other)
{
    this->vehicleId = other.vehicleId;
    this->slotId = other.slotId;
    this->departureTime = other.departureTime;
}

void VehicleDeparture::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->vehicleId);
    doParsimPacking(b,this->slotId);
    doParsimPacking(b,this->departureTime);
}

void VehicleDeparture::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->vehicleId);
    doParsimUnpacking(b,this->slotId);
    doParsimUnpacking(b,this->departureTime);
}

int VehicleDeparture::getVehicleId() const
{
    return this->vehicleId;
}

void VehicleDeparture::setVehicleId(int vehicleId)
{
    this->vehicleId = vehicleId;
}

int VehicleDeparture::getSlotId() const
{
    return this->slotId;
}

void VehicleDeparture::setSlotId(int slotId)
{
    this->slotId = slotId;
}

omnetpp::simtime_t VehicleDeparture::getDepartureTime() const
{
    return this->departureTime;
}

void VehicleDeparture::setDepartureTime(omnetpp::simtime_t departureTime)
{
    this->departureTime = departureTime;
}

class VehicleDepartureDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_vehicleId,
        FIELD_slotId,
        FIELD_departureTime,
    };
  public:
    VehicleDepartureDescriptor();
    virtual ~VehicleDepartureDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VehicleDepartureDescriptor)

VehicleDepartureDescriptor::VehicleDepartureDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VehicleDeparture)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

VehicleDepartureDescriptor::~VehicleDepartureDescriptor()
{
    delete[] propertyNames;
}

bool VehicleDepartureDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VehicleDeparture *>(obj)!=nullptr;
}

const char **VehicleDepartureDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VehicleDepartureDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VehicleDepartureDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int VehicleDepartureDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_vehicleId
        FD_ISEDITABLE,    // FIELD_slotId
        FD_ISEDITABLE,    // FIELD_departureTime
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *VehicleDepartureDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vehicleId",
        "slotId",
        "departureTime",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int VehicleDepartureDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vehicleId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "slotId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "departureTime") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *VehicleDepartureDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_vehicleId
        "int",    // FIELD_slotId
        "omnetpp::simtime_t",    // FIELD_departureTime
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **VehicleDepartureDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VehicleDepartureDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VehicleDepartureDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VehicleDepartureDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VehicleDeparture'", field);
    }
}

const char *VehicleDepartureDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VehicleDepartureDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: return long2string(pp->getVehicleId());
        case FIELD_slotId: return long2string(pp->getSlotId());
        case FIELD_departureTime: return simtime2string(pp->getDepartureTime());
        default: return "";
    }
}

void VehicleDepartureDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId(string2long(value)); break;
        case FIELD_slotId: pp->setSlotId(string2long(value)); break;
        case FIELD_departureTime: pp->setDepartureTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleDeparture'", field);
    }
}

omnetpp::cValue VehicleDepartureDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: return pp->getVehicleId();
        case FIELD_slotId: return pp->getSlotId();
        case FIELD_departureTime: return pp->getDepartureTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VehicleDeparture' as cValue -- field index out of range?", field);
    }
}

void VehicleDepartureDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_slotId: pp->setSlotId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_departureTime: pp->setDepartureTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleDeparture'", field);
    }
}

const char *VehicleDepartureDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VehicleDepartureDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VehicleDepartureDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleDeparture *pp = omnetpp::fromAnyPtr<VehicleDeparture>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleDeparture'", field);
    }
}

Register_Class(VehicleEntry)

VehicleEntry::VehicleEntry(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

VehicleEntry::VehicleEntry(const VehicleEntry& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

VehicleEntry::~VehicleEntry()
{
}

VehicleEntry& VehicleEntry::operator=(const VehicleEntry& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void VehicleEntry::copy(const VehicleEntry& other)
{
    this->vehicleId = other.vehicleId;
    this->slotId = other.slotId;
}

void VehicleEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->vehicleId);
    doParsimPacking(b,this->slotId);
}

void VehicleEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->vehicleId);
    doParsimUnpacking(b,this->slotId);
}

int VehicleEntry::getVehicleId() const
{
    return this->vehicleId;
}

void VehicleEntry::setVehicleId(int vehicleId)
{
    this->vehicleId = vehicleId;
}

int VehicleEntry::getSlotId() const
{
    return this->slotId;
}

void VehicleEntry::setSlotId(int slotId)
{
    this->slotId = slotId;
}

class VehicleEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_vehicleId,
        FIELD_slotId,
    };
  public:
    VehicleEntryDescriptor();
    virtual ~VehicleEntryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VehicleEntryDescriptor)

VehicleEntryDescriptor::VehicleEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VehicleEntry)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

VehicleEntryDescriptor::~VehicleEntryDescriptor()
{
    delete[] propertyNames;
}

bool VehicleEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VehicleEntry *>(obj)!=nullptr;
}

const char **VehicleEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VehicleEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VehicleEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int VehicleEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_vehicleId
        FD_ISEDITABLE,    // FIELD_slotId
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *VehicleEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vehicleId",
        "slotId",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int VehicleEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vehicleId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "slotId") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *VehicleEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_vehicleId
        "int",    // FIELD_slotId
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **VehicleEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VehicleEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VehicleEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VehicleEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VehicleEntry'", field);
    }
}

const char *VehicleEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VehicleEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: return long2string(pp->getVehicleId());
        case FIELD_slotId: return long2string(pp->getSlotId());
        default: return "";
    }
}

void VehicleEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId(string2long(value)); break;
        case FIELD_slotId: pp->setSlotId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleEntry'", field);
    }
}

omnetpp::cValue VehicleEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: return pp->getVehicleId();
        case FIELD_slotId: return pp->getSlotId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VehicleEntry' as cValue -- field index out of range?", field);
    }
}

void VehicleEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_slotId: pp->setSlotId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleEntry'", field);
    }
}

const char *VehicleEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VehicleEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VehicleEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleEntry *pp = omnetpp::fromAnyPtr<VehicleEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleEntry'", field);
    }
}

Register_Class(SlotAssignment)

SlotAssignment::SlotAssignment(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SlotAssignment::SlotAssignment(const SlotAssignment& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SlotAssignment::~SlotAssignment()
{
}

SlotAssignment& SlotAssignment::operator=(const SlotAssignment& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SlotAssignment::copy(const SlotAssignment& other)
{
    this->vehicleId = other.vehicleId;
    this->slotId = other.slotId;
    this->assignmentTime = other.assignmentTime;
}

void SlotAssignment::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->vehicleId);
    doParsimPacking(b,this->slotId);
    doParsimPacking(b,this->assignmentTime);
}

void SlotAssignment::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->vehicleId);
    doParsimUnpacking(b,this->slotId);
    doParsimUnpacking(b,this->assignmentTime);
}

int SlotAssignment::getVehicleId() const
{
    return this->vehicleId;
}

void SlotAssignment::setVehicleId(int vehicleId)
{
    this->vehicleId = vehicleId;
}

int SlotAssignment::getSlotId() const
{
    return this->slotId;
}

void SlotAssignment::setSlotId(int slotId)
{
    this->slotId = slotId;
}

omnetpp::simtime_t SlotAssignment::getAssignmentTime() const
{
    return this->assignmentTime;
}

void SlotAssignment::setAssignmentTime(omnetpp::simtime_t assignmentTime)
{
    this->assignmentTime = assignmentTime;
}

class SlotAssignmentDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_vehicleId,
        FIELD_slotId,
        FIELD_assignmentTime,
    };
  public:
    SlotAssignmentDescriptor();
    virtual ~SlotAssignmentDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SlotAssignmentDescriptor)

SlotAssignmentDescriptor::SlotAssignmentDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SlotAssignment)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SlotAssignmentDescriptor::~SlotAssignmentDescriptor()
{
    delete[] propertyNames;
}

bool SlotAssignmentDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SlotAssignment *>(obj)!=nullptr;
}

const char **SlotAssignmentDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SlotAssignmentDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SlotAssignmentDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SlotAssignmentDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_vehicleId
        FD_ISEDITABLE,    // FIELD_slotId
        FD_ISEDITABLE,    // FIELD_assignmentTime
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SlotAssignmentDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vehicleId",
        "slotId",
        "assignmentTime",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SlotAssignmentDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vehicleId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "slotId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "assignmentTime") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SlotAssignmentDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_vehicleId
        "int",    // FIELD_slotId
        "omnetpp::simtime_t",    // FIELD_assignmentTime
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SlotAssignmentDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SlotAssignmentDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SlotAssignmentDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SlotAssignmentDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SlotAssignment'", field);
    }
}

const char *SlotAssignmentDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SlotAssignmentDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: return long2string(pp->getVehicleId());
        case FIELD_slotId: return long2string(pp->getSlotId());
        case FIELD_assignmentTime: return simtime2string(pp->getAssignmentTime());
        default: return "";
    }
}

void SlotAssignmentDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId(string2long(value)); break;
        case FIELD_slotId: pp->setSlotId(string2long(value)); break;
        case FIELD_assignmentTime: pp->setAssignmentTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SlotAssignment'", field);
    }
}

omnetpp::cValue SlotAssignmentDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: return pp->getVehicleId();
        case FIELD_slotId: return pp->getSlotId();
        case FIELD_assignmentTime: return pp->getAssignmentTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SlotAssignment' as cValue -- field index out of range?", field);
    }
}

void SlotAssignmentDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleId: pp->setVehicleId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_slotId: pp->setSlotId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_assignmentTime: pp->setAssignmentTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SlotAssignment'", field);
    }
}

const char *SlotAssignmentDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SlotAssignmentDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SlotAssignmentDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SlotAssignment *pp = omnetpp::fromAnyPtr<SlotAssignment>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SlotAssignment'", field);
    }
}

Register_Class(SensorMalfunction)

SensorMalfunction::SensorMalfunction(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SensorMalfunction::SensorMalfunction(const SensorMalfunction& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SensorMalfunction::~SensorMalfunction()
{
}

SensorMalfunction& SensorMalfunction::operator=(const SensorMalfunction& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SensorMalfunction::copy(const SensorMalfunction& other)
{
    this->sensorId = other.sensorId;
    this->repairDuration = other.repairDuration;
}

void SensorMalfunction::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sensorId);
    doParsimPacking(b,this->repairDuration);
}

void SensorMalfunction::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sensorId);
    doParsimUnpacking(b,this->repairDuration);
}

int SensorMalfunction::getSensorId() const
{
    return this->sensorId;
}

void SensorMalfunction::setSensorId(int sensorId)
{
    this->sensorId = sensorId;
}

double SensorMalfunction::getRepairDuration() const
{
    return this->repairDuration;
}

void SensorMalfunction::setRepairDuration(double repairDuration)
{
    this->repairDuration = repairDuration;
}

class SensorMalfunctionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sensorId,
        FIELD_repairDuration,
    };
  public:
    SensorMalfunctionDescriptor();
    virtual ~SensorMalfunctionDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SensorMalfunctionDescriptor)

SensorMalfunctionDescriptor::SensorMalfunctionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SensorMalfunction)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SensorMalfunctionDescriptor::~SensorMalfunctionDescriptor()
{
    delete[] propertyNames;
}

bool SensorMalfunctionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SensorMalfunction *>(obj)!=nullptr;
}

const char **SensorMalfunctionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SensorMalfunctionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SensorMalfunctionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SensorMalfunctionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sensorId
        FD_ISEDITABLE,    // FIELD_repairDuration
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SensorMalfunctionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sensorId",
        "repairDuration",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SensorMalfunctionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sensorId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "repairDuration") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SensorMalfunctionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sensorId
        "double",    // FIELD_repairDuration
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SensorMalfunctionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SensorMalfunctionDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SensorMalfunctionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SensorMalfunctionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SensorMalfunction'", field);
    }
}

const char *SensorMalfunctionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SensorMalfunctionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        case FIELD_sensorId: return long2string(pp->getSensorId());
        case FIELD_repairDuration: return double2string(pp->getRepairDuration());
        default: return "";
    }
}

void SensorMalfunctionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        case FIELD_sensorId: pp->setSensorId(string2long(value)); break;
        case FIELD_repairDuration: pp->setRepairDuration(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SensorMalfunction'", field);
    }
}

omnetpp::cValue SensorMalfunctionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        case FIELD_sensorId: return pp->getSensorId();
        case FIELD_repairDuration: return pp->getRepairDuration();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SensorMalfunction' as cValue -- field index out of range?", field);
    }
}

void SensorMalfunctionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        case FIELD_sensorId: pp->setSensorId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_repairDuration: pp->setRepairDuration(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SensorMalfunction'", field);
    }
}

const char *SensorMalfunctionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SensorMalfunctionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SensorMalfunctionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SensorMalfunction *pp = omnetpp::fromAnyPtr<SensorMalfunction>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SensorMalfunction'", field);
    }
}

Register_Class(SensorRepair)

SensorRepair::SensorRepair(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SensorRepair::SensorRepair(const SensorRepair& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SensorRepair::~SensorRepair()
{
}

SensorRepair& SensorRepair::operator=(const SensorRepair& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SensorRepair::copy(const SensorRepair& other)
{
    this->sensorId = other.sensorId;
}

void SensorRepair::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sensorId);
}

void SensorRepair::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sensorId);
}

int SensorRepair::getSensorId() const
{
    return this->sensorId;
}

void SensorRepair::setSensorId(int sensorId)
{
    this->sensorId = sensorId;
}

class SensorRepairDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sensorId,
    };
  public:
    SensorRepairDescriptor();
    virtual ~SensorRepairDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SensorRepairDescriptor)

SensorRepairDescriptor::SensorRepairDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SensorRepair)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SensorRepairDescriptor::~SensorRepairDescriptor()
{
    delete[] propertyNames;
}

bool SensorRepairDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SensorRepair *>(obj)!=nullptr;
}

const char **SensorRepairDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SensorRepairDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SensorRepairDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SensorRepairDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sensorId
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SensorRepairDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sensorId",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SensorRepairDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sensorId") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SensorRepairDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sensorId
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SensorRepairDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SensorRepairDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SensorRepairDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SensorRepairDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SensorRepair'", field);
    }
}

const char *SensorRepairDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SensorRepairDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        case FIELD_sensorId: return long2string(pp->getSensorId());
        default: return "";
    }
}

void SensorRepairDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        case FIELD_sensorId: pp->setSensorId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SensorRepair'", field);
    }
}

omnetpp::cValue SensorRepairDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        case FIELD_sensorId: return pp->getSensorId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SensorRepair' as cValue -- field index out of range?", field);
    }
}

void SensorRepairDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        case FIELD_sensorId: pp->setSensorId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SensorRepair'", field);
    }
}

const char *SensorRepairDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SensorRepairDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SensorRepairDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SensorRepair *pp = omnetpp::fromAnyPtr<SensorRepair>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SensorRepair'", field);
    }
}

Register_Class(SimulationEnd)

SimulationEnd::SimulationEnd(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SimulationEnd::SimulationEnd(const SimulationEnd& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SimulationEnd::~SimulationEnd()
{
}

SimulationEnd& SimulationEnd::operator=(const SimulationEnd& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SimulationEnd::copy(const SimulationEnd& other)
{
}

void SimulationEnd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
}

void SimulationEnd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
}

class SimulationEndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SimulationEndDescriptor();
    virtual ~SimulationEndDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SimulationEndDescriptor)

SimulationEndDescriptor::SimulationEndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SimulationEnd)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SimulationEndDescriptor::~SimulationEndDescriptor()
{
    delete[] propertyNames;
}

bool SimulationEndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SimulationEnd *>(obj)!=nullptr;
}

const char **SimulationEndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SimulationEndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SimulationEndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SimulationEndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SimulationEndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SimulationEndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SimulationEndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SimulationEndDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SimulationEndDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SimulationEndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SimulationEndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SimulationEnd'", field);
    }
}

const char *SimulationEndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SimulationEndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SimulationEndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SimulationEnd'", field);
    }
}

omnetpp::cValue SimulationEndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SimulationEnd' as cValue -- field index out of range?", field);
    }
}

void SimulationEndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SimulationEnd'", field);
    }
}

const char *SimulationEndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SimulationEndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SimulationEndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SimulationEnd *pp = omnetpp::fromAnyPtr<SimulationEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SimulationEnd'", field);
    }
}

Register_Class(NextArrival)

NextArrival::NextArrival(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

NextArrival::NextArrival(const NextArrival& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

NextArrival::~NextArrival()
{
}

NextArrival& NextArrival::operator=(const NextArrival& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void NextArrival::copy(const NextArrival& other)
{
}

void NextArrival::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
}

void NextArrival::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
}

class NextArrivalDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    NextArrivalDescriptor();
    virtual ~NextArrivalDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(NextArrivalDescriptor)

NextArrivalDescriptor::NextArrivalDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(NextArrival)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

NextArrivalDescriptor::~NextArrivalDescriptor()
{
    delete[] propertyNames;
}

bool NextArrivalDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NextArrival *>(obj)!=nullptr;
}

const char **NextArrivalDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *NextArrivalDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int NextArrivalDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int NextArrivalDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *NextArrivalDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int NextArrivalDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *NextArrivalDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **NextArrivalDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NextArrivalDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NextArrivalDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void NextArrivalDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'NextArrival'", field);
    }
}

const char *NextArrivalDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NextArrivalDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void NextArrivalDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NextArrival'", field);
    }
}

omnetpp::cValue NextArrivalDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'NextArrival' as cValue -- field index out of range?", field);
    }
}

void NextArrivalDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NextArrival'", field);
    }
}

const char *NextArrivalDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr NextArrivalDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void NextArrivalDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    NextArrival *pp = omnetpp::fromAnyPtr<NextArrival>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NextArrival'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

