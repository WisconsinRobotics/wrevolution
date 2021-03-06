#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include "controlGroup.h"

using std::string;
using std::vector;
using MotorLib::ControlGroup;

namespace MotorLib {
    class Group : public ControlGroup {
        public:
            Group(string aName);
            string getName() const override;
            void addControlGroup(std::shared_ptr<ControlGroup> cg);
            void removeControlGroup(std::shared_ptr<ControlGroup> cg);
            string getMembers() const override;
            void setPower(double power) override;
            void setReversal(bool inverted) override;
            void setZeroPowerBehavior(ZeroPowerBehavior inputBehavior) override;
            std::shared_ptr<ControlGroup> getControlGroup (string aName);
            void clearGroup();
            std::optional<double> getEncoder() const override;
            void setPrimaryEncoder(std::shared_ptr<ControlGroup> cg);
            void resetSettings() const override;

        private:
            std::shared_ptr<ControlGroup> encoderRead;
            string name;
            vector<std::shared_ptr<ControlGroup>> members;
    };
}

#endif