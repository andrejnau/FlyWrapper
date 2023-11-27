#include "Geometry/Bones.h"
#include "Geometry/IMesh.h"

struct IModel {
    virtual void AddMesh(const IMesh& mesh) = 0;
    virtual Bones& GetBones() = 0;
};
