package temp.ast;

public class Literal extends Expression {
    private final Object value;

    public Literal(Object value) {
        this.value = value;
    }
}
