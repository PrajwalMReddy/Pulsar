package org.codepulsar.lang.variables;

import org.codepulsar.lang.Instruction;
import org.codepulsar.primitives.PrimitiveType;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;

public class FunctionVariable {
    private final LinkedHashMap<String, Function> variables;

    public FunctionVariable() {
        this.variables = new LinkedHashMap<>();
    }

    public void addFunction(String name, int arity, PrimitiveType returnType) {
        this.variables.put(name, new Function(arity, returnType));
    }

    public void setChunk(String name, ArrayList<Instruction> chunk) {
        this.variables.get(name).setChunk(chunk);
    }

    public HashMap<String, Function> getVariables() {
        return this.variables;
    }

    public static class Function {
        private ArrayList<Instruction> chunk;

        private final int arity;
        private final PrimitiveType returnType;

        public Function(int arity, PrimitiveType returnType) {
            this.chunk = null;

            this.arity = arity;
            this.returnType = returnType;
        }

        public ArrayList<Instruction> getChunk() {
            return this.chunk;
        }

        public void setChunk(ArrayList<Instruction> chunk) {
            this.chunk = chunk;
        }
    }
}
