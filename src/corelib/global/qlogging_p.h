// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QLOGGING_P_H
#define QLOGGING_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of a number of Qt sources files.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/private/qglobal_p.h>
#include "qlogging.h"
#include "qloggingcategory.h"
#include "qvarlengtharray.h"

QT_BEGIN_NAMESPACE

namespace QtPrivate {

Q_CORE_EXPORT bool shouldLogToStderr();

}

class QInternalMessageLogContext : public QMessageLogContext
{
public:
    static constexpr int DefaultBacktraceDepth = 32;
    using BacktraceStorage = QVarLengthArray<void *, DefaultBacktraceDepth>;
    std::optional<BacktraceStorage> backtrace;

    Q_ALWAYS_INLINE QInternalMessageLogContext(const QMessageLogContext &logContext)
    {
        int backtraceFrames = initFrom(logContext);
        if (backtraceFrames)
            populateBacktrace(backtraceFrames);
    }
    QInternalMessageLogContext(const QMessageLogContext &logContext,
                               const QLoggingCategory &categoryOverride)
        : QInternalMessageLogContext(logContext)
    {
        category = categoryOverride.categoryName();
    }

    int initFrom(const QMessageLogContext &logContext);
    void populateBacktrace(int frameCount);
};

QT_END_NAMESPACE

#endif // QLOGGING_P_H
