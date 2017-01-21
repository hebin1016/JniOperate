//
//  main.c
//  LearnJNI
//
//  Created by hebin on 2017/1/17.
//  Copyright © 2017年 hebin. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "com_hank_learnjni_LearnJni.h"
#ifdef __cplusplus
extern "C"
{
#endif
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    getStringFromC
     * Signature: ()Ljava/lang/String;
     */
    JNIEXPORT jstring JNICALL Java_com_hank_learnjni_LearnJni_getStringFromC
    (JNIEnv *env, jclass jclass){
        
        return (*env)->NewStringUTF(env,"from c string");
        
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    getStringFromC1
     * Signature: ()Ljava/lang/String;
     */
    JNIEXPORT jstring JNICALL Java_com_hank_learnjni_LearnJni_getStringFromC1
    (JNIEnv *env, jobject jobject){
        return (*env)->NewStringUTF(env,"from c string1");
        
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    changeName
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_changeName
    (JNIEnv *env, jobject jobject){
       //获取jobject的对象
       jclass jclass=(*env)->GetObjectClass(env,jobject);
       //获取fieldid
       jfieldID fid=(*env)->GetFieldID(env,jclass,"name","Ljava/lang/String;");
        
       jstring new_str=(*env)->NewStringUTF(env,"my name is hank");
        
        (*env)->SetObjectField(env,jobject,fid,new_str);
        
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    accessStaticField
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_accessStaticField
    (JNIEnv *env, jobject jobject){
        jclass jcs=(*env)->GetObjectClass(env,jobject);
        jfieldID jfid=(*env)->GetStaticFieldID(env,jcs,"money","I");
        jint jmoney=(*env)->GetStaticIntField(env,jcs,jfid);
        jmoney++;
        (*env)->SetStaticIntField(env,jcs,jfid,jmoney);
    }

    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    accessArrayField
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_accessArrayField
    (JNIEnv *env, jobject jobject){
        jclass jclass=(*env)->GetObjectClass(env,jobject);
        jfieldID jfi=(*env)->GetFieldID(env,jclass,"stars","[Ljava/lang/String;");
        printf("GetFieldID\n");
        jobjectArray jarray=(jobjectArray)(*env)->GetObjectField(env,jclass,jfi);
        printf("GetObjectField\n");
        (*env)->SetObjectArrayElement(env,jarray,0,(*env)->NewStringUTF(env,"hank"));
    }

    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    accessMethod
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_accessMethod
    (JNIEnv *env, jobject jobject){
        jclass jcs=(*env)->GetObjectClass(env,jobject);
        jmethodID jmi=(*env)->GetMethodID(env,jcs,"getRandomInt","(I)I");
        jint random=(*env)->CallIntMethod(env,jobject,jmi,100);
        printf("random:%d",random);
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    accessStaticMethod
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_accessStaticMethod
    (JNIEnv *env, jobject jobject){
        jclass jcs=(*env)->GetObjectClass(env,jobject);
        jmethodID jmi=(*env)->GetStaticMethodID(env,jcs,"getUUID","()Ljava/lang/String;");
        jstring uuid=(*env)->CallStaticObjectMethod(env,jcs,jmi);
        //jstring->char*
        //isCopy JNI_FALSE 代表java和c操作的是同一个字符串
        const char *uuid_str=(*env)->GetStringUTFChars(env,uuid,JNI_FALSE);
        char filename[100];
        sprintf(filename, "/Users/hebin/Downloads/%s.txt",uuid_str);
        FILE *fp=fopen(filename, "w");
        fputs("i am hank", fp);
        fclose(fp);
        
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    accessConstructorMethod
     * Signature: ()V
     * 访问构造方法
     * 用java.util.Date产生一个当前的时间戳
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_accessConstructorMethod
    (JNIEnv *env, jobject job){
        jclass jcs=(*env)->FindClass(env,"java/util/Date");
        jmethodID jmd=(*env)->GetMethodID(env,jcs,"<init>","()V");
        //实例化一个Date对象
        jobject data_obj=(*env)->NewObject(env,jcs,jmd);
        //调用getTime方法
        jmethodID gettime_mid=(*env)->GetMethodID(env,jcs,"getTime","()J");
        jlong time=(*env)->CallLongMethod(env,data_obj,gettime_mid);
        
        printf("time:%ld",time);
    }

    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    accessNonvirtualMethod
     * Signature: ()V
     * 调用父类的方法
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_accessNonvirtualMethod
    (JNIEnv *env, jobject jobj){
        jclass jcs= (*env)->GetObjectClass(env,jobj);
        //获取people对象（child的实例）
        jfieldID peole_fid=(*env)->GetFieldID(env,jcs,"people","Lcom/hank/learnjni/People;");
        jobject people_obj= (*env)->GetObjectField(env,jobj,peole_fid);
        //执行父类的方法
        jclass people_class=(*env)->FindClass(env,"com/hank/learnjni/People");//注意：要调用哪个父类的方法，就传哪个父类
        jmethodID say_methodid=(*env)->GetMethodID(env,people_class,"say","()V");
        
        //(*env)->CallObjectMethod(env,people_obj,say_methodid);
        //调用父类的方法
        (*env)->CallNonvirtualObjectMethod(env,people_obj,people_class,say_methodid);
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    chineseChars
     * Signature: (Ljava/lang/String;)V
     */
    JNIEXPORT jstring JNICALL Java_com_hank_learnjni_LearnJni_chineseChars
    (JNIEnv *env, jobject jobject, jstring jst){
//        const char *c_str=(*env)->GetStringUTFChars(env,jstring,JNI_FALSE);
//        printf("name:%s",c_str);
          char *c_str="我是大牛";
//        jstring jstr=(*env)->NewStringUTF(env,c_str);
//        
        //执行java方法 String(byte bytes[],String charsetName)构造方法所需的条件
        
   //     jclass string_jclass=(*env)->FindClass(env,"java/lang/String");
       // jmethodID string_mid=(*env)->GetMethodID(env,string_jclass,"<init>","([BLjava/lang/String;)V");
        
        //jbyte->char
     //   jbyteArray jbarray=(*env)->NewByteArray(env,strlen(c_str));
        //byte数组赋值
        //0->strlen(c_str)
     //   (*env)->SetByteArrayRegion(env,jbarray,0,strlen(c_str),(jbyte *)c_str);
        
        
      //  jstring encode=(*env)->NewStringUTF(env,"utf-8");
        
        //调用构造方法
      //  return (*env)->NewObject(env,string_jclass,string_mid,jbarray,encode);
        
        return (*env)->NewStringUTF(env,c_str);
    }

    int compare(const void* a,const void* b){
        return (*(int*)a)-(*(int*)b);
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    getArray
     * Signature: ([I)V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_giveArray
    (JNIEnv *env, jobject jobj, jintArray jintarray){
        //拿到指针
       jint *p_array=(*env)->GetIntArrayElements(env,jintarray,JNI_FALSE);
        // 取长度
        int len=(*env)->GetArrayLength(env,jintarray);
        //排序
        qsort(p_array,len,sizeof(jint),compare);
        //释放同步
        //第四个参数:0,java数组进行更新，并且释放c/c++数组
        //JNI_ABORT,java数组不进行更新，释放c/c++代码
        //JNI_COMMIT,java数组进行更新，不释放c/c++代码(函数执行完，才会被释放)
        (*env)->ReleaseIntArrayElements(env,jintarray,p_array,0);
    }
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    getArray
     * Signature: ()[I
     * 返回数组
     */
    JNIEXPORT jintArray JNICALL Java_com_hank_learnjni_LearnJni_getArray
    (JNIEnv *env, jobject jobj,jint len){
        jintArray jarray=(*env)->NewIntArray(env,len);
        jint *p=(*env)->GetIntArrayElements(env,jarray,NULL);
        int i=0;
        for (; i<len; i++) {
            p[i]=i;
        }
        //同步
        (*env)->ReleaseIntArrayElements(env,jarray,p,0);
        
        return jarray;
    }

    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    localDef
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_localDef
    (JNIEnv *env, jobject jobj){
        jclass date_class=(*env)->FindClass(env,"java/util/Date");
        jmethodID date_mid=(*env)->GetMethodID(env,date_class,"<init>","()V");
        jobject date_obj=(*env)->NewObject(env,date_class,date_mid);
        
        //不再使用date_obj对象了
        //通知垃圾回收器回收这些对象
        (*env)->DeleteLocalRef(env,date_obj);
    }
    
    
    jstring global_name;
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    createGlobalRef
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_createGlobalRef
    (JNIEnv *env, jobject jobj){
        jstring name=(*env)->NewStringUTF(env,"hank.he");
        global_name=(*env)->NewGlobalRef(env,name);
    }
    
    
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    getGlobalRef
     * Signature: ()V
     */
    JNIEXPORT jstring JNICALL Java_com_hank_learnjni_LearnJni_getGlobalRef
    (JNIEnv *env, jobject jobj){
        return global_name;
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    deleteGlobalRef
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_deleteGlobalRef
    (JNIEnv *env, jobject jobj){
        (*env)->DeleteGlobalRef(env,global_name);
    }
    
    /*
     * Class:     com_hank_learnjni_LearnJni
     * Method:    exception
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_com_hank_learnjni_LearnJni_exception
    (JNIEnv *env, jobject jobj){
        jclass jcs=(*env)->GetObjectClass(env,jobj);
        jfieldID name_fid=(*env)->GetFieldID(env,jcs,"name1","Ljava/lang/String;");
        jthrowable ex=(*env)->ExceptionOccurred(env);
        if(0!=ex){
            (*env)->ExceptionClear(env);
            name_fid=(*env)->GetFieldID(env,jcs,"name","Ljava/lang/String;");
        }
        jstring name_str=(*env)->GetObjectField(env,jobj,name_fid);
        const char *c_str=(*env)->GetStringUTFChars(env,name_str,JNI_FALSE);
        printf("name:%s",c_str);
    }

    int main()
    {
        return 0;
    }
