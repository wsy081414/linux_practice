


struct mm_struct {
	
	//指向线性区对象的链表头
	struct vm_area_struct * mmap;		/* list of VMAs */
	//指向线性区对象的红黑树
	struct rb_root mm_rb;
	//指向最近找到的虚拟区间
	struct vm_area_struct * mmap_cache;	/* last find_vma result */
	
	//用来在进程地址空间中搜索有效的进程地址空间的函数
	unsigned long (*get_unmapped_area) (struct file *filp,
				unsigned long addr, unsigned long len,
				unsigned long pgoff, unsigned long flags);
				
       unsigned long (*get_unmapped_exec_area) (struct file *filp,
				unsigned long addr, unsigned long len,
				unsigned long pgoff, unsigned long flags);

	//释放线性区时调用的方法，			
	void (*unmap_area) (struct mm_struct *mm, unsigned long addr);
	
	//标识第一个分配文件内存映射的线性地址
	unsigned long mmap_base;		/* base of mmap area */
	
	
	unsigned long task_size;		/* size of task vm space */
	/*
	 * RHEL6 special for bug 790921: this same variable can mean
	 * two different things. If sysctl_unmap_area_factor is zero,
	 * this means the largest hole below free_area_cache. If the
	 * sysctl is set to a positive value, this variable is used
	 * to count how much memory has been munmapped from this process
	 * since the last time free_area_cache was reset back to mmap_base.
	 * This is ugly, but necessary to preserve kABI.
	 */
	unsigned long cached_hole_size;
	
	//内核进程搜索进程地址空间中线性地址的空间空间
	unsigned long free_area_cache;		/* first hole of size cached_hole_size or larger */
	
	//指向页表的目录
	pgd_t * pgd;
	
	//共享进程时的个数
	atomic_t mm_users;			/* How many users with user space? */
	
	//内存描述符的主使用计数器，采用引用计数的原理，当为0时代表无用户再次使用
	atomic_t mm_count;			/* How many references to "struct mm_struct" (users count as 1) */
	
	//线性区的个数
	int map_count;				/* number of VMAs */
	
	struct rw_semaphore mmap_sem;
	
	//保护任务页表和引用计数的锁
	spinlock_t page_table_lock;		/* Protects page tables and some counters */

	//mm_struct结构，第一个成员就是初始化的mm_struct结构，
	struct list_head mmlist;		/* List of maybe swapped mm's.	These are globally strung
						 * together off init_mm.mmlist, and are protected
						 * by mmlist_lock
						 */

	/* Special counters, in some configurations protected by the
	 * page_table_lock, in other configurations by being atomic.
	 */
	 
	mm_counter_t _file_rss;
	mm_counter_t _anon_rss;
	mm_counter_t _swap_usage;

	//进程拥有的最大页表数目
	unsigned long hiwater_rss;	/* High-watermark of RSS usage */、
	//进程线性区的最大页表数目
	unsigned long hiwater_vm;	/* High-water virtual memory usage */

	//进程地址空间的大小，锁住无法换页的个数，共享文件内存映射的页数，可执行内存映射中的页数
	unsigned long total_vm, locked_vm, shared_vm, exec_vm;
	//用户态堆栈的页数，
	unsigned long stack_vm, reserved_vm, def_flags, nr_ptes;
	//维护代码段和数据段
	unsigned long start_code, end_code, start_data, end_data;
	//维护堆和栈
	unsigned long start_brk, brk, start_stack;
	//维护命令行参数，命令行参数的起始地址和最后地址，以及环境变量的起始地址和最后地址
	unsigned long arg_start, arg_end, env_start, env_end;

	unsigned long saved_auxv[AT_VECTOR_SIZE]; /* for /proc/PID/auxv */

	struct linux_binfmt *binfmt;

	cpumask_t cpu_vm_mask;

	/* Architecture-specific MM context */
	mm_context_t context;

	/* Swap token stuff */
	/*
	 * Last value of global fault stamp as seen by this process.
	 * In other words, this value gives an indication of how long
	 * it has been since this task got the token.
	 * Look at mm/thrash.c
	 */
	unsigned int faultstamp;
	unsigned int token_priority;
	unsigned int last_interval;
	
	//线性区的默认访问标志
	unsigned long flags; /* Must use atomic bitops to access the bits */

	struct core_state *core_state; /* coredumping support */
#ifdef CONFIG_AIO
	spinlock_t		ioctx_lock;
	struct hlist_head	ioctx_list;
#endif
#ifdef CONFIG_MM_OWNER
	/*
	 * "owner" points to a task that is regarded as the canonical
	 * user/owner of this mm. All of the following must be true in
	 * order for it to be changed:
	 *
	 * current == mm->owner
	 * current->mm != mm
	 * new_owner->mm == mm
	 * new_owner->alloc_lock is held
	 */
	struct task_struct *owner;
#endif

#ifdef CONFIG_PROC_FS
	/* store ref to file /proc/<pid>/exe symlink points to */
	struct file *exe_file;
	unsigned long num_exe_file_vmas;
#endif
#ifdef CONFIG_MMU_NOTIFIER
	struct mmu_notifier_mm *mmu_notifier_mm;
#endif
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	pgtable_t pmd_huge_pte; /* protected by page_table_lock */
#endif
	/* reserved for Red Hat */
#ifdef __GENKSYMS__
	unsigned long rh_reserved[2];
#else
	/* How many tasks sharing this mm are OOM_DISABLE */
	union {
		unsigned long rh_reserved_aux;
		atomic_t oom_disable_count;
	};

	/* base of lib map area (ASCII armour) */
	unsigned long shlib_base;
#endif
};
