public class MatrixHelper {
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

    public static float[] getRotationMatrix(double pAngle, float x, float y, float z) {
        float angle = (float)Math.toRadians(pAngle);
        if(x > 0)
            return new float[]{ 1,0,0,0,
                                0,(float)Math.cos(angle),(float)Math.sin(angle),0,
                                0,(float)-Math.sin(angle),(float)Math.cos(angle),0,
                                0,0,0,1 };
        else if(y > 0)
            return new float[]{ (float)Math.cos(angle),0,(float)-Math.sin(angle),0,
                                0,1,0,0,
                                (float)Math.sin(angle),0,(float)Math.cos(angle),0,
                                0,0,0,1 };
        else
            return new float[]{ (float)Math.cos(angle),(float)Math.sin(angle),0,0,
                    (float)-Math.sin(angle),(float)Math.cos(angle),0,0,
                    0,0,1,0,
                    0,0,0,1 };
    }

    public static float[] getTranslationMatrix(float x, float y, float z) {
        return new float[]{ 1,0,0,0,
                            0,1,0,0,
                            0,0,1,0,
                            x,y,z,1
                            };
    }
}
