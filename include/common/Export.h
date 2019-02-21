#ifndef EXPORT_H
#define EXPORT_H
#define _CRT_SECURE_NO_WARNINGS

#ifdef EXPORT_H
#define JDCG_EXPORT_API __declspec(dllexport)
#else
#define JDCG_EXPORT_API __declspec(dllimport)
#endif

#endif // !EXPORT_H
