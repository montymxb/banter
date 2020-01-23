:: Various Notes

# Performance Notes
- tests performed on Dec. 3rd, 2019
- comparing the original to this program
- hypothesis: this program can produce visuals of higher resolution, with higher point count, with less memory per point
- tested on /data/db/parse_db.0 (67.1 MB database file)

- Banter 1.0 (Obj-C w/ OpenGL) stats
  - program size: 556kb
  - max points viewable: 262144
  - RAM per
    - 66k points (fixed): 110 MB
  - CPU per
    - 66k points (fixed): 30%

- Banter 2.0 (C w/ OpenGL) stats
  - program size: 42kb
  - max points viewable: 500k (1 million w/ slowdown)
  - RAM per
    - 10k points: 18 MB
    - 66k points: 25 MB
    - 100k points: 29 MB
    - 500k points: 72 MB
    - 1mil points: 95 MB
  - CPU per
    - 10k points: 14% (6.1% stationary)
    - 66k points: 24% (14.5% stationary)
    - 100k points: 30%
    - 500k points: 68%
    - 1mil points: 88%

- Results
  - program 2.0 is 1400% smaller than the original program size
  - program 2.0 can render 200%-400% more points
  - program 2.0 has a 340% smaller memory footprint than program 1.0 (for 66k points)
  - program 2.0 has a 25% smaller CPU footprint than program 1.0 (for 66k points)

- Conclusions
  - program 2.0 is superior in all measurements (memory footprint, # of points, program size, % cpu usage)
  - program 2.0 has a much higher CPU % utilization as expected, the reduction over program 1.0 is only slight
  - it appears program 2.0 is heavily CPU bound, similar to program 1.0 (as expected)
  - anything that will reduce the CPU usage will result in significant increases in practical analysis limitations
