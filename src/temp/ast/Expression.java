package temp.ast;

import temp.lang.Visitor;

public abstract class Expression {
    public abstract <R> R accept(Visitor<R> visitor);
}
