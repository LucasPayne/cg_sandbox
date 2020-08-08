#ifndef RESOURCE_MODEL_REFERENCE
#define RESOURCE_MODEL_REFERENCE


class ResourceModel;


struct ResourceModelReference {
    ResourceModelReference(TableHandle _handle) : handle{_handle} {}
    ResourceModelReference() {}
    TableHandle handle;
    ResourceModel &operator*();
    ResourceModel *operator->();
};


#endif // RESOURCE_MODEL_REFERENCE
