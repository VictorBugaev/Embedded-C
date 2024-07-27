#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>//для файлов устройств
#include <linux/rwlock.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/kobject.h>
   

static int major = 0;
static rwlock_t lock;
static char test_string[15] = "Hellooo!!!\n";

static struct proc_dir_entry *test = NULL;

static struct kobject *test_kobj = NULL;

static ssize_t string_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
    
    size_t rc = 0;
    memcpy(buf, test_string, 15);
    rc = strlen(test_string);
    return rc;
}

static ssize_t string_store(struct kobject *kobj, struct kobj_attribute *attr, char const *buf, size_t count){
    
    size_t rc = 0;
    memcpy(test_string, buf, count);
    rc = strlen(buf );
    return rc;

}
static ssize_t test_proc_read(struct file *fd, char __user *buff, size_t size, loff_t *off){
    
    size_t rc = 0;
    rc = simple_read_from_buffer(buff, size, off, test_string, 15);
    
    return rc;
}

static ssize_t test_proc_write(struct file *fd, char const __user *buff, size_t size, loff_t *off){
    
    size_t rc = 0;
    rc = simple_write_to_buffer(test_string, 15, off, buff, size);
    
    return rc;
}


static ssize_t test_read(struct file *fd, char __user *buff, size_t size, loff_t *off){
    size_t rc;
    read_lock (&lock);
    rc = simple_read_from_buffer(buff, size, off, test_string, 15);
    read_unlock(&lock);
    
    return rc;
}

static ssize_t test_write(struct file *fd, char const __user *buff, size_t size, loff_t *off){
    size_t rc = 0;
    if (size > 15){
        return -EINVAL;
    }
    write_lock (&lock);
    rc = simple_write_to_buffer(test_string, 15, off, buff, size);
    write_unlock(&lock);
    
    return rc;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = test_read,
    .write = test_write
};

static const struct proc_ops pops = {
    .proc_read = test_proc_read,
    .proc_write = test_proc_write,
};

static struct kobj_attribute string_attribute = __ATTR(test_string, 0644, string_show, string_store);

static struct attribute *attrs[] = 
{
    &string_attribute.attr, 
    NULL,
};

static struct attribute_group attr_group = 
{
    .attrs = attrs,
};


int init_module(void){
    pr_info("This module was loaded!\n");
    rwlock_init(&lock);
    major = register_chrdev(major, "my_module", &fops);
    if(major < 0){
        return major;
    }
    pr_info("Major number -  %d\n", major);
    int retval = 0;    
    test = proc_create("my_module", 0666, NULL, &pops);//создание файла для proc
    
    test_kobj = kobject_create_and_add("my_kobject", kernel_kobj);

    if(!test_kobj){
        return -ENOMEM;
    }
    
    retval = sysfs_create_group(test_kobj, &attr_group);

    if (retval){
        kobject_put(test_kobj);
        return retval;
    }
    return 0;
}

void cleanup_module(void){
    unregister_chrdev(major, "my_module");
    proc_remove(test);
    kobject_put(test_kobj);
}

MODULE_LICENSE("GPL");
