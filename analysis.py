#!/usr/bin/env python3
"""
Sorting Algorithms Performance Analysis
E-Commerce Fulfillment Center Pipeline
CLEAN MINIMALIST DASHBOARD
"""

import matplotlib.pyplot as plt
import numpy as np

# Set style for clean look
plt.style.use('default')
plt.rcParams['font.size'] = 10
plt.rcParams['axes.labelsize'] = 11
plt.rcParams['axes.titlesize'] = 12
plt.rcParams['figure.titlesize'] = 16

def create_clean_dashboard():
    """Create a clean, organized dashboard with all phases"""
    
    print("\n" + "="*60)
    print("📊 GENERATING CLEAN SORTING DASHBOARD")
    print("="*60)
    
    # Create figure with 2x3 grid
    fig, axes = plt.subplots(2, 3, figsize=(16, 10))
    fig.suptitle('E-Commerce Sorting Pipeline - Performance Dashboard', 
                 fontsize=18, fontweight='bold', color='#2c3e50', y=0.98)
    
    # Colors
    green = '#27ae60'
    red = '#e74c3c'
    blue = '#3498db'
    orange = '#e67e22'
    purple = '#9b59b6'
    
    # ============================================================
    # 1. PHASE 1: Micro-Scale (Top Left)
    # ============================================================
    ax1 = axes[0, 0]
    
    categories = ['Random', 'Nearly Sorted']
    insertion = [15, 2]
    selection = [45, 42]
    
    x = np.arange(len(categories))
    width = 0.35
    
    bars1 = ax1.bar(x - width/2, insertion, width, label='Insertion Sort', 
                    color=green, alpha=0.8)
    bars2 = ax1.bar(x + width/2, selection, width, label='Selection Sort', 
                    color=red, alpha=0.8)
    
    ax1.set_ylabel('Time (μs)')
    ax1.set_title('Phase 1: Micro-Scale (N=50)', fontweight='bold')
    ax1.set_xticks(x)
    ax1.set_xticklabels(categories)
    ax1.legend(loc='upper left', frameon=False)
    ax1.grid(True, alpha=0.15, axis='y')
    ax1.set_ylim(0, 55)
    
    # Add labels
    for bar in bars1:
        ax1.text(bar.get_x() + bar.get_width()/2., bar.get_height() + 1,
                f'{int(bar.get_height())}', ha='center', va='bottom', fontweight='bold')
    for bar in bars2:
        ax1.text(bar.get_x() + bar.get_width()/2., bar.get_height() + 1,
                f'{int(bar.get_height())}', ha='center', va='bottom', fontweight='bold')
    
    # Speedup note
    ax1.text(0.5, 0.92, '⚡ 21x faster on sorted data', 
            transform=ax1.transAxes, ha='center', fontsize=9, 
            color=green, fontweight='bold',
            bbox=dict(boxstyle='round', facecolor='white', alpha=0.8, edgecolor=green))
    
    # ============================================================
    # 2. PHASE 2: VIP Extraction (Top Center)
    # ============================================================
    ax2 = axes[0, 1]
    
    methods = ['Full Sort\n+ Top 500', 'Heap\n+ Extract']
    times = [8500, 320]
    
    bars = ax2.bar(methods, times, color=[red, green], alpha=0.8)
    ax2.set_ylabel('Time (μs)')
    ax2.set_title('Phase 2: VIP Extraction', fontweight='bold')
    ax2.grid(True, alpha=0.15, axis='y')
    ax2.set_ylim(0, 9500)
    
    for bar, value in zip(bars, times):
        ax2.text(bar.get_x() + bar.get_width()/2., bar.get_height() + 200,
                f'{value:,}', ha='center', va='bottom', fontweight='bold')
    
    speedup = times[0] / times[1]
    ax2.text(0.5, 0.92, f'⚡ {speedup:.1f}x faster', 
            transform=ax2.transAxes, ha='center', fontsize=9, 
            color=green, fontweight='bold',
            bbox=dict(boxstyle='round', facecolor='white', alpha=0.8, edgecolor=green))
    
    # ============================================================
    # 3. PHASE 3: Macro-Scale (Top Right)
    # ============================================================
    ax3 = axes[0, 2]
    
    sizes = [10000, 50000, 100000, 500000, 1000000]
    heap_times = [500, 3200, 7800, 50000, 120000]
    radix_times = [800, 3800, 7500, 40000, 85000]
    
    ax3.plot(sizes, heap_times, 'o-', label='Heap Sort', 
             color=red, linewidth=2, markersize=6)
    ax3.plot(sizes, radix_times, 's-', label='Radix Sort', 
             color=blue, linewidth=2, markersize=6)
    ax3.set_xlabel('Dataset Size')
    ax3.set_ylabel('Time (μs)')
    ax3.set_title('Phase 3: Macro-Scale', fontweight='bold')
    ax3.legend(loc='upper left', frameon=False)
    ax3.grid(True, alpha=0.15)
    ax3.set_xscale('log')
    ax3.set_yscale('log')
    
    # Crossover
    ax3.axvline(x=100000, color='green', linestyle='--', alpha=0.5)
    ax3.text(100000, 2000, 'Crossover\nat 100K', ha='center', fontsize=8)
    
    # ============================================================
    # 4. BONUS: Memory Bandwidth (Bottom Left)
    # ============================================================
    ax4 = axes[1, 0]
    
    types = ['32-bit', '64-bit']
    times64 = [120, 210]
    
    bars = ax4.bar(types, times64, color=[blue, orange], alpha=0.8)
    ax4.set_ylabel('Time (ms)')
    ax4.set_title('Bonus: Memory Bandwidth', fontweight='bold')
    ax4.grid(True, alpha=0.15, axis='y')
    ax4.set_ylim(0, 250)
    
    for bar, value in zip(bars, times64):
        ax4.text(bar.get_x() + bar.get_width()/2., bar.get_height() + 5,
                f'{value}ms', ha='center', va='bottom', fontweight='bold')
    
    slowdown = times64[1] / times64[0]
    ax4.text(0.5, 0.92, f'⚠️ {slowdown:.1f}x slower', 
            transform=ax4.transAxes, ha='center', fontsize=9, 
            color=orange, fontweight='bold',
            bbox=dict(boxstyle='round', facecolor='white', alpha=0.8, edgecolor=orange))
    
    # ============================================================
    # 5. SUMMARY STATISTICS (Bottom Center)
    # ============================================================
    ax5 = axes[1, 1]
    ax5.axis('off')
    
    summary = """PERFORMANCE SUMMARY

Phase 1: Micro-Scale
  • Insertion Sort: 2 μs (sorted)
  • Selection Sort: 42 μs
  • ✅ 21x faster on sorted data

Phase 2: VIP Extraction
  • Full Sort: 8,500 μs
  • Heap Extract: 320 μs
  • ✅ 26.6x faster!

Phase 3: Macro-Scale
  • Radix Sort wins at N=100,000
  • O(n) vs O(n log n)

Bonus: Memory Bandwidth
  • 64-bit: 1.75x slower
  • Double memory = cache misses"""
    
    ax5.text(0, 0.95, summary, transform=ax5.transAxes,
            fontsize=9, verticalalignment='top', fontfamily='monospace',
            bbox=dict(boxstyle='round', facecolor='#f8f9fa', alpha=0.8, edgecolor='#dee2e6'))
    
    # ============================================================
    # 6. SPEEDUP COMPARISON (Bottom Right)
    # ============================================================
    ax6 = axes[1, 2]
    
    phases = ['Phase 1', 'Phase 2', 'Phase 3']
    speedups = [21.0, 26.6, 1.41]
    colors6 = [green, blue, purple]
    
    bars = ax6.bar(phases, speedups, color=colors6, alpha=0.8, width=0.5)
    ax6.set_ylabel('Speedup (x)')
    ax6.set_title('Speedup Comparison', fontweight='bold')
    ax6.grid(True, alpha=0.15, axis='y')
    ax6.set_ylim(0, 30)
    
    for bar, value in zip(bars, speedups):
        ax6.text(bar.get_x() + bar.get_width()/2., bar.get_height() + 0.5,
                f'{value}x', ha='center', va='bottom', fontweight='bold')
    
    ax6.axhline(y=1, color='red', linestyle='--', alpha=0.5)
    ax6.text(2, 1.5, 'Break-even', ha='center', fontsize=8, color='red')
    
    # Bottom note
    ax6.text(0.5, -0.15, 'Higher = Better Performance', 
            transform=ax6.transAxes, ha='center', fontsize=8, style='italic')
    
    # ============================================================
    # FINALIZE
    # ============================================================
    
    plt.tight_layout()
    plt.subplots_adjust(top=0.93)
    plt.savefig('sorting_dashboard_clean.png', dpi=300, bbox_inches='tight', 
                facecolor='white')
    plt.show()
    
    print("\n✅ Clean dashboard saved as: sorting_dashboard_clean.png")
    print("\n" + "="*60)

if __name__ == "__main__":
    create_clean_dashboard()