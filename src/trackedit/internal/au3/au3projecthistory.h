/*
* Audacity: A Digital Audio Editor
*/

#pragma once

#include "iprojecthistory.h"

#include "context/iglobalcontext.h"
#include "modularity/ioc.h"

#include "au3wrap/au3types.h"

#include "libraries/lib-utility/Observer.h"

namespace au::trackedit {
class Au3ProjectHistory : public IProjectHistory
{
    muse::Inject<context::IGlobalContext> globalContext;

public:
    void init() override;

    bool undoAvailable() override;
    void undo() override;
    bool redoAvailable() override;
    void redo() override;
    void pushHistoryState(
        const std::string& longDescription, const std::string& shortDescription) override;
    void pushHistoryState(
        const std::string& longDescription, const std::string& shortDescription, UndoPushType flags) override;
    void rollbackState() override;
    void modifyState(bool autoSave) override;
    void markUnsaved() override;
    void startUserInteraction() override;
    void endUserInteraction() override;
    muse::async::Notification isUndoRedoAvailableChanged() const override;

private:
    au3::Au3Project& projectRef();

    bool m_interactionOngoing = false;
    muse::async::Notification m_isUndoRedoAvailableChanged;
    ::Observer::Subscription m_undoRedoMessageSubscription;
};
}
