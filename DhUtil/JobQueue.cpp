#include "pch.h"
#include "JobQueue.h"

void JobQueue::Push(JobRef&& _job)
{
	// 순서 중요 - count 증가 후 push, job 실행 후 count 감소
	const int32 prevCount = m_jobCount.fetch_add(1);
	m_jobs.Push(_job); // WRITE_LOCK

	// 첫번째 Job을 넣은 쓰레드가 실행까지 담당
	if (prevCount == 0)
	{
		Execute();
	}
}

// TODO : 
// 1. 일감이 한번에, 그리고 계속 너무 몰리는 상황
// 2. DoAsync 함수를 계속 타서(DoAsync해서 실행한 함수 안에 또 DoAsync가 있는 등...) 
//    절대 끝나지 않는 상황 (일감이 한 쓰레드한테 몰리는 상황)
void JobQueue::Execute()
{
    while (true)
    {
        std::vector<JobRef> jobs;
        m_jobs.PopAll(OUT jobs);

        const int32 jobCount = static_cast<int32>(jobs.size());
        for (int32 i = 0; i < jobCount; i++)
        {
            try
            {
                jobs[i]->Execute();
            }
            catch (const std::exception& e)
            {
                // 작업 실행 중 예외 처리
                std::cerr << "Job execution failed: " << e.what() << std::endl;
            }
        }

        // 일감이 더 이상 없으면 중단
        if (m_jobCount.fetch_sub(jobCount) == jobCount)
        {
            return;
        }

        // 처리 후 잠시 대기 (CPU 과부하 방지)
        // std::this_thread::yield();
    }
}