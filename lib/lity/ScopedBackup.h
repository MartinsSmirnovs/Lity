#pragma once

template <class BackupedType>
class ScopedBackup {
public:
    ScopedBackup(BackupedType& backupElement)
    : backupElement(backupElement),
      backup(backupElement) {
    }

    ~ScopedBackup() {
        backupElement = backup;
    }

private:
    BackupedType& backupElement;
    const BackupedType backup;
};
