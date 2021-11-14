#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glut.h>
#include "glCho.h"

using namespace std;
struct Vertex {
    float x, y, z;
};
struct Face {
    int vi[3];
};
struct Normal {
    float norFace[3];
    float norV1[3], norV2[3], norV3[3];
};
class Mesh {
    int nVtx = 0;
    Vertex* vertex = NULL;
    int nFace = 0;
    Face* face = NULL;
    Normal* normal = NULL;

public:
    Mesh() {}
    ~Mesh() { clearAse(); }
    void clearAse() {
        if (nVtx != 0)
            delete[] vertex;
        if (nFace != 0) {
            delete[] face;
            delete[] normal;
        }
        nVtx = nFace = 0;
    }
    void readAse(const char* fileName)
    {
        FILE* fp;
        char line[256], str[40];
        float _x, _y, _z;
        int num = 0;
        if ((fp = fopen(fileName, "r")) == NULL)
        {
            cout << "File is Not Found" << endl;
            return;
        }
        while (fgets(line, 256, fp) != NULL)
        {
            sscanf(line, "%s", str);
            if (strcmp(str, "*MESH") == 0)
            {
                fgets(line, 256, fp);
                fgets(line, 256, fp);
                sscanf(line, "%s%d", str, &nVtx);
                fgets(line, 256, fp);
                sscanf(line, "%s %d", str, &nFace);

                vertex = new Vertex[nVtx];
                face = new Face[nFace];
                normal = new Normal[nFace];
                fgets(line, 256, fp);
                sscanf(line, "%s", str);
                if (strcmp(str, "*MESH_VERTEX_LIST") == 0)
                {
                    for (int i = 0; i < nVtx; i++)
                    {
                        fgets(line, 256, fp);
                        sscanf(line, "%s%d%f%f%f", str, &num, &_x, &_y, &_z);
                        vertex[i].x = _x;
                        vertex[i].y = _z;
                        vertex[i].z = _y;
                    }
                }
                fgets(line, 256, fp);
                fgets(line, 256, fp);
                sscanf(line, "%s", str);
                if (strcmp(str, "*MESH_FACE_LIST") == 0) {
                    for (int i = 0; i < nFace; i++) {
                        fgets(line, 256, fp);
                        sscanf(line, "%s%s%s%d%s%d%s%d%s%d%s%d%s%d%s",
                            str, str, str,
                            &(face[i].vi[0]), str,
                            &(face[i].vi[1]), str,
                            &(face[i].vi[2]), str,
                            &num, str, &num, str, &num, str);
                    }
                }

                fgets(line, 256, fp);
                fgets(line, 256, fp);
                sscanf(line, "%s", str);
                if (strcmp(str, "*MESH_NUMCVERTEX") == 0) {
                    fgets(line, 256, fp);
                    sscanf(line, "%s", str);
                }
                if (strcmp(str, "*MESH_NORMALS") == 0) {
                    for (int i = 0; i < nFace; i++) {
                        float* nF = normal[i].norFace;
                        float* nV1 = normal[i].norV1;
                        float* nV2 = normal[i].norV2;
                        float* nV3 = normal[i].norV3;

                        fgets(line, 256, fp);
                        sscanf(line, "%s%d%f%f%f", str, &num, nF, nF + 1, nF + 2);
                        fgets(line, 256, fp);
                        sscanf(line, "%s%d%f%f%f", str, &num, nV1, nV1 + 1, nV1 + 2);
                        fgets(line, 256, fp);
                        sscanf(line, "%s%d%f%f%f", str, &num, nV2, nV2 + 1, nV2 + 2);
                        fgets(line, 256, fp);
                        sscanf(line, "%s%d%f%f%f", str, &num, nV3, nV3 + 1, nV3 + 2);
                    }
                }
                break;
            }
        }
        fclose(fp);

    }
    void setColor(float r, float g, float b, float a) {
        float color[4] = { r, g, b, a };
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    }
    void draw(float scale = 1.0f, bool bCoord = false)
    {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < nFace; i++)
        {
            Vertex* v1 = &vertex[face[i].vi[0]];
            Vertex* v2 = &vertex[face[i].vi[1]];
            Vertex* v3 = &vertex[face[i].vi[2]];
            glNormal3fv(normal[i].norV1);
            glVertex3f(v1->x / scale, v1->y / scale, v1->z / scale);
            glNormal3fv(normal[i].norV2);
            glVertex3f(v2->x / scale, v2->y / scale, v2->z / scale);
            glNormal3fv(normal[i].norV3);
            glVertex3f(v3->x / scale, v3->y / scale, v3->z / scale);
        }
        glEnd();
        if (bCoord) {
            glChoCoord(1.0);
        }
    }
    void draw(float r, float g, float b, float scale = 1.0f, bool bCoord = false) {
        setColor(r, g, b, 1.0);
        draw(scale, bCoord);
    }
};