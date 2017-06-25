#pragma once
/*
*  Wavefront .obj file format reader.
*
*  author: Nate Robins
*  email: ndr@pobox.com
*  www: http://www.pobox.com/~ndr
*/

/* includes */
#include <gl/glut.h>


#ifndef M_PI
#define M_PI 3.14159265
#endif


/* defines */
#define GLM_NONE     (0)			/* render with only vertices */
#define GLM_FLAT     (1 << 0)		/* render with facet normals */
#define GLM_SMOOTH   (1 << 1)		/* render with vertex normals */
#define GLM_TEXTURE  (1 << 2)		/* render with texture coords */
#define GLM_COLOR    (1 << 3)		/* render with colors */
#define GLM_MATERIAL (1 << 4)		/* render with materials */


/* structs */

/* GLMmaterial: Structure that defines a material in a model.
*/
typedef struct _GLMmaterial
{
	char* name;						/* name of material */
	GLfloat diffuse[4];				/* diffuse component */
	GLfloat ambient[4];				/* ambient component */
	GLfloat specular[4];			/* specular component */
	GLfloat emmissive[4];			/* emmissive component */
	GLfloat shininess;				/* specular exponent */
} GLMmaterial;

/* GLMtriangle: Structure that defines a triangle in a model.
*/
typedef struct {
	GLuint vindices[3];				/* array of triangle vertex indices */
	GLuint nindices[3];				/* array of triangle normal indices */
	GLuint tindices[3];				/* array of triangle texcoord indices*/
	GLuint findex;					/* index of triangle facet normal */
} GLMtriangle;

/* GLMgroup: Structure that defines a group in a model.
*/
typedef struct _GLMgroup {
	char*             name;			/* name of this group */
	GLuint            numtriangles;	/* number of triangles in this group */
	GLuint*           triangles;	/* array of triangle indices */
	GLuint            material;     /* index to material for group */
	struct _GLMgroup* next;			/* pointer to next group in model */
} GLMgroup;

/* GLMmodel: Structure that defines a model.
*/
typedef struct {
	char*    pathname;				/* path to this model */
	char*    mtllibname;			/* name of the material library */

	GLuint   numvertices;			/* number of vertices in model */
	GLfloat* vertices;				/* array of vertices  */

	GLuint   numnormals;			/* number of normals in model */
	GLfloat* normals;				/* array of normals */

	GLuint   numtexcoords;			/* number of texcoords in model */
	GLfloat* texcoords;				/* array of texture coordinates */

	GLuint   numfacetnorms;			/* number of facetnorms in model */
	GLfloat* facetnorms;			/* array of facetnorms */

	GLuint       numtriangles;		/* number of triangles in model */
	GLMtriangle* triangles;			/* array of triangles */

	GLuint       nummaterials;		/* number of materials in model */
	GLMmaterial* materials;			/* array of materials */

	GLuint       numgroups;			/* number of groups in model */
	GLMgroup*    groups;			/* linked list of groups */

	GLfloat position[3];			/* position of the model */

} GLMmodel;


/* public functions */

/* glmReadOBJ: Reads a model description from a Wavefront .OBJ file.
* Returns a pointer to the created object which should be free'd with
* glmDelete().
*
* filename - name of the file containing the Wavefront .OBJ format data.
*/
GLMmodel*
glmReadOBJ(char* filename);

/* glmDraw: Renders the model to the current OpenGL context using the
* mode specified.
*
* model    - initialized GLMmodel structure
* mode     - a bitwise OR of values describing what is to be rendered.
*            GLM_NONE    -  render with only vertices
*            GLM_FLAT    -  render with facet normals
*            GLM_SMOOTH  -  render with vertex normals
*            GLM_TEXTURE -  render with texture coords
*            GLM_FLAT and GLM_SMOOTH should not both be specified.
*/
GLvoid
glmDraw(GLMmodel* model, GLuint mode);

/* glmDrawTransparency: Renders the model to the current OpenGL context using the
* mode and transparency specified.
*
* model    - initialized GLMmodel structure
* mode     - a bitwise OR of values describing what is to be rendered.
*            GLM_NONE     -  render with only vertices
*            GLM_FLAT     -  render with facet normals
*            GLM_SMOOTH   -  render with vertex normals
*            GLM_TEXTURE  -  render with texture coords
*            GLM_COLOR    -  render with colors (color material)
*            GLM_MATERIAL -  render with materials
*            GLM_COLOR and GLM_MATERIAL should not both be specified.
*            GLM_FLAT and GLM_SMOOTH should not both be specified.
* transparency
*          - transparency of the model
*/
GLvoid
glmDrawTransparency(GLMmodel* model, GLuint mode, GLfloat transparency);
