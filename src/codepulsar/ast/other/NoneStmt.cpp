#include "NoneStmt.h"


Pulsar::NoneStmt::NoneStmt() {
}

std::any Pulsar::NoneStmt::accept(Pulsar::StmtVisitor& visitor) {
    return visitor.visitNoneStatement(this);
}
