#ifndef __CGCPREDICATES_H__
#define __CGCPREDICATES_H__

	//double err;

  #ifdef __cplusplus
    extern "C" {
  #endif

	void exactinit ( void );
	double orient2d      ( double* pa, double* pb, double* pc );
	double orient2dfast  ( double* pa, double* pb, double* pc );
	double orient2dexact ( double* pa, double* pb, double* pc );
	double orient2dslow  ( double* pa, double* pb, double* pc );

	double orient3d      ( double* pa, double* pb, double* pc, double* pd );
	double orient3dfast  ( double* pa, double* pb, double* pc, double* pd );
	double orient3dexact ( double* pa, double* pb, double* pc, double* pd );
	double orient3dslow  ( double* pa, double* pb, double* pc, double* pd );

	double incircle      ( double* pa, double* pb, double* pc, double* pd );
	double incirclefast  ( double* pa, double* pb, double* pc, double* pd );
	double incircleexact ( double* pa, double* pb, double* pc, double* pd );
	double incircleslow  ( double* pa, double* pb, double* pc, double* pd );

	double insphere      ( double* pa, double* pb, double* pc, double* pd, double* pe );
	double inspherefast  ( double* pa, double* pb, double* pc, double* pd, double* pe );
	double insphereexact ( double* pa, double* pb, double* pc, double* pd, double* pe );
	double insphereslow  ( double* pa, double* pb, double* pc, double* pd, double* pe );

	void doubleprint ( double number );

	double getfpuprecision ( void );

  #ifdef __cplusplus
  }
  #endif

#endif // __CGCPREDICATES_H__
