import org.ejml.simple.SimpleMatrix;

import java.lang.String;
import java.lang.System;

public class Blarg {
    public static float[] multiplyMatrices(float[] matrixA, float[] matrixB) {
        float[][] doubleMatrixA = makeDoubleMatrix(matrixA);
        float[][] doubleMatrixB = makeDoubleMatrix(matrixB);
        float[][] matrix3 = new float[4][4];
        float temp1 = 0;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    temp1 = temp1 + doubleMatrixA[i][k] * doubleMatrixB[k][j];
                }
                matrix3[i][j] = temp1;
                temp1 = 0;
            }
        }
        return makeSingleMatrix(matrix3);
    }

    private static float[] makeSingleMatrix(float[][] matrix3) {
        float[] result = new float[16];
        int counter = 0;

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                result[counter] = matrix3[i][j];
                counter++;
            }
        }
        return result;
    }


    private static float[][] makeDoubleMatrix(float[] matrixA) {
        float[][] result = new float[4][4];
        int rowOffset = 0;

        for(int i = 0; i < matrixA.length / 4; i++) {
            System.arraycopy(matrixA, rowOffset, result[i], 0, matrixA.length / 4);
            rowOffset += 4;
        }
        return result;
    }

    public static void main(String[] args) {
        float[] matrixA = {2,1,2,1,3,2,1,2,3,2,1,2,5,2,4,3};
        float[] matrixB = {2,2,2,2,3,6,3,2,5,2,5,3,4,3,3,2};

        for(int i = 0; i < 16; i++) {
            System.out.println(Blarg.multiplyMatrices(matrixA, matrixB)[i]);
        }

    }
}
