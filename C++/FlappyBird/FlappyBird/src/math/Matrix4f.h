class Matrix4f
{
public:
	static const int SIZE = 4 * 4;
	float* matrix = new float[SIZE];

	Matrix4f() {}

	static Matrix4f indentity()
	{
		Matrix4f result;

		for (int i = 0; i < SIZE; i++)
		{
			result.matrix[i] = 0.0f;
		}

		result.matrix[0 + 0 * 4] = 1.0f;
		result.matrix[1 + 1 * 4] = 1.0f;
		result.matrix[2 + 2 * 4] = 1.0f;
		result.matrix[3 + 3 * 4] = 1.0f;

		return result;
	}

	Matrix4f multiply(Matrix4f matrix) {
		Matrix4f result;

		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += this->matrix[x + e * 4] * matrix.matrix[e + y * 4];
				}
				result.matrix[x + y * 4] = sum;
			}
		}
		return result;
	}

	static Matrix4f translate(Vector3f vector) {
		Matrix4f result = identity();

		result.matrix[0 + 3 * 4] = vector.x;
		result.matrix[1 + 3 * 4] = vector.y;
		result.matrix[2 + 3 * 4] = vector.z;

		return result;
	}

	static Matrix4f rotate(float angle) {
		Matrix4f result = identity();
		float r = (float)Math.toRadians(angle);
		float cos = (float)Math.cos(r);
		float sin = (float)Math.sin(r);

		result.matrix[0 + 0 * 4] = cos;
		result.matrix[1 + 0 * 4] = sin;

		result.matrix[0 + 1 * 4] = -sin;
		result.matrix[1 + 1 * 4] = cos;

		return result;
	}
};