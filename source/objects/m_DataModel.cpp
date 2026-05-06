#include "objects/m_DataModel.h"

namespace Mariner {

    namespace Objects {

        m_DataModel* m_DataModel::New() {

            static m_DataModel* Instance = new m_DataModel();
            Instance->Name = "DataModel";
            Instance->ClassName = "m_DataModel";
            return Instance;

        }

    }

}