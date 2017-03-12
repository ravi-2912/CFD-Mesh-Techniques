#pragma once



namespace ExtraLib
{
	/*
	* This code is a part of NeHe tutorials and was converted from native C++ into managed C++.
	* Matrix/Vector manipulations have been updated.
	* Updation done by Ravinder Singh
	*/
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Text;
	using namespace System::Drawing;
	using namespace System::Windows;
	using namespace System::Windows::Forms;

	public ref class Point2f
	{
	public:
		float x, y;

		Point2f(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
	};

	public ref class Quat4f
	{
	public:
		float x, y, z, w;
	};

	public ref class Vector3f
	{
	public:
		float x, y, z;

		Vector3f()
		{
		}

		Vector3f(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}

		static void cross(Vector3f ^Result, Vector3f ^v1, Vector3f ^v2)
		{
			Result->x = (v1->y * v2->z) - (v1->z * v2->y);
			Result->y = (v1->z * v2->x) - (v1->x * v2->z);
			Result->z = (v1->x * v2->y) - (v1->y * v2->x);
		}

		static float dot(Vector3f ^v1, Vector3f ^v2)
		{
			return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z + v2->z);
		}

		float length()
		{
			return safe_cast<float>(System::Math::Sqrt(x * x + y * y + z * z));
		}
	};

	public ref class arcball
	{
	private:
		literal float Epsilon = 1.0e-5f;

		Vector3f ^StVec; //Saved click vector
		Vector3f ^EnVec; //Saved drag vector
		float adjustWidth; //Mouse bounds width
		float adjustHeight; //Mouse bounds height

	public:
		arcball(float NewWidth, float NewHeight)
		{
			StVec = gcnew Vector3f();
			EnVec = gcnew Vector3f();
			setBounds(NewWidth, NewHeight);
		}

	private:
		void mapToSphere(Point ^point, Vector3f ^vector)
		{
			Point2f ^tempPoint = gcnew Point2f((float)point->X, (float)point->Y);

			//Adjust point coords and scale down to range of [-1 ... 1]
			tempPoint->x = (tempPoint->x * this->adjustWidth) - 1.0f;
			tempPoint->y = 1.0f - (tempPoint->y * this->adjustHeight);

			//Compute square of the length of the vector from this point to the center
			float length = (tempPoint->x * tempPoint->x) + (tempPoint->y * tempPoint->y);

			//If the point is mapped outside the sphere... (length > radius squared)
			if (length > 1.0f)
			{
				//Compute a normalizing factor (radius / sqrt(length))
				float norm = safe_cast<float>(1.0 / Math::Sqrt(length));

				//Return the "normalized" vector, a point on the sphere
				vector->x = tempPoint->x * norm;
				vector->y = tempPoint->y * norm;
				vector->z = 0.0f;
			}
			//Else it's inside
			else
			{
				//Return a vector to a point mapped inside the sphere sqrt(radius squared - length)
				vector->x = tempPoint->x;
				vector->y = tempPoint->y;
				vector->z = safe_cast<float>(System::Math::Sqrt(1.0f - length));
			}
		}

	public:
		void setBounds(float NewWidth, float NewHeight)
		{
			//Set adjustment factor for width/height
			adjustWidth = 1.0f / ((NewWidth - 1.0f) * 0.5f);
			adjustHeight = 1.0f / ((NewHeight - 1.0f) * 0.5f);
		}

		//Mouse down
		virtual void click(Point NewPt)
		{
			mapToSphere(NewPt, this->StVec);
		}

		//Mouse drag, calculate rotation
		void drag(Point NewPt, Quat4f ^NewRot)
		{
			//Map the point to the sphere
			this->mapToSphere(NewPt, EnVec);

			//Return the quaternion equivalent to the rotation
			if (NewRot != nullptr)
			{
				Vector3f ^Perp = gcnew Vector3f();

				//Compute the vector perpendicular to the begin and end vectors
				Vector3f::cross(Perp, StVec, EnVec);

				//Compute the length of the perpendicular vector
				if (Perp->length() > Epsilon)
					//if its non-zero
				{
					//We're ok, so return the perpendicular vector as the transform after all
					NewRot->x = Perp->x;
					NewRot->y = Perp->y;
					NewRot->z = Perp->z;
					//In the quaternion values, w is cosine (theta / 2), where theta is the rotation angle
					NewRot->w = Vector3f::dot(StVec, EnVec);
				}
				//if it is zero
				else
				{
					//The begin and end vectors coincide, so return an identity transform
					NewRot->x = NewRot->y = NewRot->z = NewRot->w = 0.0f;
				}
			}
		}
	};

	public ref class Matrix4f
	{
	private:
		array<float, 2> ^M;
		float scl;
		Vector3f ^pan;

	public:
		Matrix4f()
		{
			InitializeInstanceFields();
			SetIdentity();
		}

		void get_Renamed(array<float> ^dest)
		{
			int k = 0;
			for (int i = 0; i <= 3; i++)
				for (int j = 0; j <= 3; j++)
				{
					dest[k] = this->M[j, i];
					k++;
				}
		}

		void SetIdentity()
		{
			this->M = gcnew array<float, 2>(4, 4); // set to zero
			for (int i = 0; i <= 3; i++)
				this->M[i, i] = 1.0f;
		}

		void set_Renamed(Matrix4f ^m1)
		{
			this->M = m1->M;
		}

		void MatrixMultiply(Matrix4f ^m1, Matrix4f ^m2)
		{
			array<float>^ MulMat = gcnew array<float>(16);
			float elMat = 0.0f;
			int k = 0;

			for (int i = 0; i <= 3; i++)
				for (int j = 0; j <= 3; j++)
				{
					for (int l = 0; l <= 3; l++)
						elMat += m1->M[i, l] * m2->M[l, j];
					MulMat[k] = elMat;
					elMat = 0.0f;
					k++;
				}

			k = 0;
			for (int i = 0; i <= 3; i++)
				for (int j = 0; j <= 3; j++)
				{
					m1->M[i, j] = MulMat[k];
					k++;
				}
		}

		property Quat4f ^Rotation
		{
			void set(Quat4f ^value)
			{
				float n, s;
				float xs, ys, zs;
				float wx, wy, wz;
				float xx, xy, xz;
				float yy, yz, zz;

				M = gcnew array<float, 2>(4, 4);

				n = (value->x * value->x) + (value->y * value->y) + (value->z * value->z) + (value->w * value->w);
				s = (n > 0.0f) ? 2.0f / n : 0.0f;

				xs = value->x * s;
				ys = value->y * s;
				zs = value->z * s;
				wx = value->w * xs;
				wy = value->w * ys;
				wz = value->w * zs;
				xx = value->x * xs;
				xy = value->x * ys;
				xz = value->x * zs;
				yy = value->y * ys;
				yz = value->y * zs;
				zz = value->z * zs;

				// rotation
				M[0, 0] = 1.0f - (yy + zz);
				M[0, 1] = xy - wz;
				M[0, 2] = xz + wy;

				M[1, 0] = xy + wz;
				M[1, 1] = 1.0f - (xx + zz);
				M[1, 2] = yz - wx;

				M[2, 0] = xz - wy;
				M[2, 1] = yz + wx;
				M[2, 2] = 1.0f - (xx + yy);

				M[3, 3] = 1.0f;

				// translation (pan)
				M[0, 3] = pan->x;
				M[1, 3] = pan->y;

				// scale (zoom)
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						M[i, j] *= scl;


			}
		}

		property float Scale
		{
			void set(float value)
			{
				scl = value;
			}

		}

		property Vector3f ^Pan
		{
			void set(Vector3f ^value)
			{
				pan = value;
			}

		}


	private:
		bool initialized;
		void InitializeInstanceFields()
		{
			if (!initialized)
			{
				scl = 1.0f;
				pan = gcnew Vector3f();

				initialized = true;
			}
		}
	};


	public ref class MouseControl
	{
	protected:
		System::Windows::Forms::Control ^newCtrl;
		MouseButtons FinalClick;

	public:
		event EventHandler ^LeftClick;
		event EventHandler ^RightClick;
		event EventHandler ^MiddleClick;

		event MouseEventHandler ^LeftMouseDown;
		event MouseEventHandler ^LeftMouseUp;
		event MouseEventHandler ^RightMouseDown;
		event MouseEventHandler ^RightMouseUp;

		event MouseEventHandler ^MiddleMouseDown;
		event MouseEventHandler ^MiddleMouseUp;

		event MouseEventHandler ^MouseWheelUp;
		event MouseEventHandler ^MouseWheelDown;

		property System::Windows::Forms::Control ^Control
		{
			System::Windows::Forms::Control ^get()
			{
				return newCtrl;
			}
			void set(System::Windows::Forms::Control ^value)
			{
				newCtrl = value;
				Initialize();
			}
		}

		MouseControl()
		{
		}

		MouseControl(System::Windows::Forms::Control ^ctrl)
		{
			Control = ctrl;
		}

		void AddControl(System::Windows::Forms::Control ^ctrl)
		{
			Control = ctrl;
		}

	protected:
		virtual void Initialize()
		{
			newCtrl->Click += gcnew EventHandler(this, &MouseControl::OnClick);
			newCtrl->MouseDown += gcnew MouseEventHandler(this, &MouseControl::OnMouseDown);
			newCtrl->MouseUp += gcnew MouseEventHandler(this, &MouseControl::OnMouseUp);
			newCtrl->MouseWheel += gcnew MouseEventHandler(this, &MouseControl::OnMouseWheelDown);
			newCtrl->MouseWheel += gcnew MouseEventHandler(this, &MouseControl::OnMouseWheelUp);


		}

	private:
		void OnClick(Object ^sender, EventArgs ^e)
		{
			switch (FinalClick)
			{
			case MouseButtons::Left:
				LeftClick(sender, e);
				break;

			case MouseButtons::Right:
				RightClick(sender, e);
				break;
			}
		}




		void OnMouseDown(Object ^sender, MouseEventArgs ^e)
		{
			FinalClick = e->Button;

			switch (e->Button)
			{
			case MouseButtons::Left:
			{
				LeftMouseDown(sender, e);
				break;
			}
			case MouseButtons::Middle:
			{
				MiddleMouseDown(sender, e);
				break;
			}

			case MouseButtons::Right:
			{
				RightMouseDown(sender, e);
				break;
			}
			}
		}

		void OnMouseUp(Object ^sender, MouseEventArgs ^e)
		{
			switch (e->Button)
			{
			case MouseButtons::Left:
			{
				LeftMouseUp(sender, e);
				break;
			}
			case MouseButtons::Middle:
			{
				MiddleMouseUp(sender, e);
				break;
			}

			case MouseButtons::Right:
			{
				RightMouseUp(sender, e);
				break;
			}
			}
		}
		void OnMouseWheelUp(Object ^sender, MouseEventArgs ^e)
		{
			int detants = (e->Delta);
			if (detants >= 0)
				MouseWheelUp(sender, e);

		}
		void OnMouseWheelDown(Object ^sender, MouseEventArgs ^e)
		{
			int detants = e->Delta;
			if (detants < 0)
				MouseWheelDown(sender, e);
		}
	};


}
